#include "encoder.h"

static rotary_encoder_t *encoder = NULL; /* 编码器 */
static SemaphoreHandle_t mutex = NULL;

static int32_t encoder_diff = 0;          /* 编码器转动方向，0为静止，1为顺时针旋转，-1为逆时针旋转 */
static bool encoder_diff_disable = false; /* 获取编码器数值，true为使能，false为失能 */
int32_t cnt;

QueueHandle_t Encoder_Mailbox;
QueueHandle_t Handle_Queue_Manual_Target_temperature;
// QueueHandle_t Handle_Mode_Change;

key_state_t encoder_push_state;

/* 编码器配置 */
void encoder_config(void)
{
    uint32_t pcnt_unit = 0;

    mutex = xSemaphoreCreateMutex();

    /* 1.配置编码器KEY GPIO */
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        // .pin_bit_mask = ENCODER_PUSH_GPIO_PIN_SEL,
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = 0, /* 允许下拉 */
        .pull_up_en = 1,
    };

    gpio_config(&io_conf);

    /* 2.配置编码器A、B */
    rotary_encoder_config_t config = ROTARY_ENCODER_DEFAULT_CONFIG((rotary_encoder_dev_t)pcnt_unit, ENCODER_A_PIN, ENCODER_B_PIN);
    ESP_ERROR_CHECK(rotary_encoder_new_ec11(&config, &encoder));
    ESP_ERROR_CHECK(encoder->set_glitch_filter(encoder, 10)); /* 滤波器 */
    ESP_ERROR_CHECK(encoder->start(encoder));
}

// static key_state_t encoder_push_scan(void)
// {
//     if (gpio_get_level(ENCODER_PUSH_PIN) == 0)
//     {
//         vTaskDelay(pdMS_TO_TICKS(20));
//         if (gpio_get_level(ENCODER_PUSH_PIN) == 0)
//         {
//             return KEY_DOWN;
//         }
//     }

//     return KEY_UP;
// }

void encoder_queue_init()
{
    Encoder_Mailbox = xQueueCreate(1, sizeof(uint));
    // Handle_Mode_Change = xQueueCreate(1, sizeof(button_mode_t));
    Handle_Queue_Manual_Target_temperature = xQueueCreate(1, sizeof(long));
}

/**
 * @brief Task for handling the encoder operations.
 *
 * This task handles the encoder operations by periodically checking the encoder state,
 * detecting key presses and direction changes, and performing corresponding actions.
 * It utilizes a mutex for synchronization and interacts with the HC165 shift register
 * for reading the encoder values. It also writes data to various mailboxes and updates
 * the mode change button state.
 *
 * @param pvParameter The task parameter (not used).
 * @return None.
 */
static void encoder_task(void *pvParameter)
{
    uint8_t key = 0;
    // HC165_encoder_pin.dataPin = 5;
    
    // button_mode_t state_mode_change = BUTTON_AUTO_READY_MODE;
    // Mode_change_button_write(state_mode_change);
    
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(150));
        if (pdTRUE == xSemaphoreTake(mutex, portMAX_DELAY))
        {
            /* 1.KEY检测 */
            // encoder_push_state = encoder_push_scan();
            // ESP_LOGI("ESP", "encoder_push_state = %d\n",encoder_push_state);

            /* 2.方向检测 */
            // if (!encoder_diff_disable)
            // {
                // 旋钮操作
                cnt = encoder->get_counter_value(encoder) / 8; /* 获取编码器数值 */
                // printf("cnt = %d\n", cnt);
                // ESP_LOGI("ESP", "cnt = %d\n", cnt);
                Encoder_queue_write(cnt);
                xSemaphoreGive(mutex);

                // key = _74HC165_read_data(&HC165_encoder_pin);
                // // printf("key = %d\n", key);
                // // 物理加热按键触发
                // if((key | 0xfe) == 0xfe)
                // {
                //     vTaskDelay(pdMS_TO_TICKS(1000));
                //     if((key | 0xfe) == 0xfe)
                //     {
                //         if(Mode_change_button_read() == BUTTON_AUTO_READY_MODE)
                //         {
                //             manual_mode_start_mailbox_write();
                //             while((key | 0xfe) == 0xfe)
                //             {
                //                 key = _74HC165_read_data(&HC165_encoder_pin);
                //                 vTaskDelay(pdMS_TO_TICKS(150));
                //             }
                //         }
                //         else if(Mode_change_button_read() == BUTTON_MANUAL_READY_MODE)
                //         {
                //             timer_start_button_event();
                //             while((key | 0xfe) == 0xfe)
                //             {
                //                 key = _74HC165_read_data(&HC165_encoder_pin);
                //                 vTaskDelay(pdMS_TO_TICKS(150));
                //             }
                //         }
                //     }
                // }
                // // 物理模式切换按键触发
                // if((key | 0xfd) == 0xfd)
                // {
                //     vTaskDelay(pdMS_TO_TICKS(150));
                //     if((key | 0xfd) == 0xfd)
                //     {
                //         state_mode_change = Mode_change_button_read();
                //         if(state_mode_change == BUTTON_AUTO_READY_MODE)
                //         {
                //             state_mode_change = BUTTON_AUTO_MODE;
                //             Mode_change_button_write(state_mode_change);
                //             while((key | 0xfd) == 0xfd)
                //             {
                //                 vTaskDelay(pdMS_TO_TICKS(150));
                //                 key = _74HC165_read_data(&HC165_encoder_pin);
                //             }
                //         }
                //         else if(state_mode_change == BUTTON_MANUAL_READY_MODE)
                //         {
                //             state_mode_change = BUTTON_MANUAL_MODE;
                //             Mode_change_button_write(state_mode_change);
                //             while((key | 0xfd) == 0xfd)
                //             {
                //                 vTaskDelay(pdMS_TO_TICKS(150));
                //                 key = _74HC165_read_data(&HC165_encoder_pin);
                //             }
                //         }    
                //         // printf("state_mode_change: %d\n", state_mode_change);
                //     }
                // }
        }
    }
}

void input_task_create(void)
{
    xTaskCreatePinnedToCore(encoder_task, "input task", 1024*8, NULL, 1, NULL, 1);
}

int Encoder_queue_read(void)
{
    int cnt = 0;
    xQueuePeek(Encoder_Mailbox, &cnt, 0);
    return cnt;
}

void Encoder_queue_write(int cnt)
{
    xQueueOverwrite(Encoder_Mailbox, &cnt);
}

int32_t encoder_get_diff(void)
{
    int32_t diff = cnt;
    return diff;
}

bool encoder_get_is_push(void)
{
    /* 编码器KEY按下不再读取方向数值 */
    if (encoder_push_state == KEY_DOWN)
    {
        encoder_diff_disable = true;
        return true;
    }
    else
    {
        encoder_diff_disable = false;
        return false;
    }
}

long Encoder_temperature_queue_read(void)
{
    long current_temperature = 0;
    xQueuePeek(Handle_Queue_Manual_Target_temperature, &current_temperature, 0);
    return current_temperature;
}

void Encoder_temperature_queue_write(long current_temperature)
{
    xQueueOverwrite(Handle_Queue_Manual_Target_temperature, &current_temperature);
}

// button_mode_t Mode_change_button_read(void)
// {
//     button_mode_t current_mode = BUTTON_MANUAL_MODE;
//     xQueuePeek(Handle_Mode_Change, &current_mode, 0);
//     return current_mode;
// }

// void Mode_change_button_write(button_mode_t current_mode)
// {
//     xQueueOverwrite(Handle_Mode_Change, &current_mode);
// }
