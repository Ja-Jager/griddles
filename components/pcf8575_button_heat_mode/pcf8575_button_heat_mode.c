#include "pcf8575_button_heat_mode.h"

QueueHandle_t Handle_Mode_Change;

i2c_dev_t pcf8575_button_heat_mode;

void pcf8575_BHM_init(void)
{
    // pcf8575_button_heat_mode
    i2cdev_init();
    // Zero device descriptor
    memset(&pcf8575_button_heat_mode, 0, sizeof(i2c_dev_t));
    // Init i2c device descriptor
    ESP_ERROR_CHECK(pcf8575_init_desc(&pcf8575_button_heat_mode, 0x20, 0, pcf8575_SDA_NUM ,pcf8575_SCL_NUM));

    Handle_Mode_Change = xQueueCreate(1, sizeof(button_mode_t));

    xTaskCreate(pcf8575_BHM_task, "pcf8575_BHM_task", 4096, NULL, 1, NULL);

    printf("can create BHM task secondly\n");
}

void pcf8575_BHM_task(void* arg)
{
    printf("can create BHM task secondly\n");
    button_mode_t state_mode_change = BUTTON_AUTO_READY_MODE;
    Mode_change_button_write(state_mode_change);
    while(1)
    {   
        vTaskDelay(pdMS_TO_TICKS(50));
        // 物理加热按键触发
        if(pcf8575_read(pcf8575_button_heat_mode, pcf8575_HEAT_NUM, 0))
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            if(pcf8575_read(pcf8575_button_heat_mode, pcf8575_HEAT_NUM, 0))
            {
                if(Mode_change_button_read() == BUTTON_AUTO_READY_MODE)
                {
                    manual_mode_start_mailbox_write();
                    while(pcf8575_read(pcf8575_button_heat_mode, pcf8575_HEAT_NUM, 0))
                    {
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }
                }
                else if(Mode_change_button_read() == BUTTON_MANUAL_READY_MODE)
                {
                    timer_start_button_event();
                    while(pcf8575_read(pcf8575_button_heat_mode, pcf8575_HEAT_NUM, 0))
                    {
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }
                }
            }
        }
        // 物理模式切换按键触发
        if(pcf8575_read(pcf8575_button_heat_mode, pcf8575_MODE_NUM, 0))
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            if(pcf8575_read(pcf8575_button_heat_mode, pcf8575_MODE_NUM, 0))
            {
                state_mode_change = Mode_change_button_read();
                if(state_mode_change == BUTTON_AUTO_READY_MODE)
                {
                    state_mode_change = BUTTON_AUTO_MODE;
                    Mode_change_button_write(state_mode_change);
                    while(pcf8575_read(pcf8575_button_heat_mode, pcf8575_MODE_NUM, 0))
                    {
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }
                }
                else if(state_mode_change == BUTTON_MANUAL_READY_MODE)
                {
                    state_mode_change = BUTTON_MANUAL_MODE;
                    Mode_change_button_write(state_mode_change);
                    while(pcf8575_read(pcf8575_button_heat_mode, pcf8575_MODE_NUM, 0))
                    {
                        vTaskDelay(pdMS_TO_TICKS(10));
                    }
                }    
                // printf("state_mode_change: %d\n", state_mode_change);
            }
        }
    }
}

bool pcf8575_read(i2c_dev_t current_pcf8575, uint8_t pcf8575_read_bit, bool pcf8575_read_state)
{
    u_int16_t current_read_val = 0x0000;
    pcf8575_port_read(&current_pcf8575, &current_read_val);
    if(pcf8575_read_state == 1)
    {
        if((current_read_val & (1 << pcf8575_read_bit)) == 1)
        {
            current_read_val &= ~(1 << pcf8575_read_bit);
            pcf8575_port_write(&current_pcf8575, current_read_val);
            return 1;
        }
        else
        {
            current_read_val &= ~(1 << pcf8575_read_bit);
            pcf8575_port_write(&current_pcf8575, current_read_val);
            return 0;
        }
    }
    else
    {
        if((current_read_val & (1 << pcf8575_read_bit)) == 0)
        {
            current_read_val |= (1 << pcf8575_read_bit);
            pcf8575_port_write(&current_pcf8575, current_read_val);
            return 1;
        }
        else
        {
            current_read_val |= (1 << pcf8575_read_bit);
            pcf8575_port_write(&current_pcf8575, current_read_val);
            return 0;
        }
    }
}

button_mode_t Mode_change_button_read(void)
{
    button_mode_t current_mode = BUTTON_MANUAL_MODE;
    xQueuePeek(Handle_Mode_Change, &current_mode, 0);
    return current_mode;
}

void Mode_change_button_write(button_mode_t current_mode)
{
    xQueueOverwrite(Handle_Mode_Change, &current_mode);
}
