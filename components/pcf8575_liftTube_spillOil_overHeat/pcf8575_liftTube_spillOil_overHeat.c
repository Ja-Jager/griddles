#include "pcf8575_liftTube_spillOil_overHeat.h"

// liftTube_spillOil_overHeat_state state = normal;
i2c_dev_t pcf8575_LSO;
QueueHandle_t handle_queue_state_use;
u_int16_t current_pcf8575_LSO_val;

liftTube_spillOil_overHeat_state state = normal;

void pcf8575_liftTube_spillOil_overHeat_init()
{
    // pcf8575_LSO
    i2cdev_init();
    // Zero device descriptor
    memset(&pcf8575_LSO, 0, sizeof(i2c_dev_t));
    // Init i2c device descriptor
    ESP_ERROR_CHECK(pcf8575_init_desc(&pcf8575_LSO, 0x20, 0, pcf8575_SDA_NUM ,pcf8575_SCL_NUM));

    handle_queue_state_use = xQueueCreate(1, sizeof(enum use_state));

    xTaskCreate(pcf8575_liftTube_spillOil_overHeat_task, "pcf8575_liftTube_spillOil_overHeat_task", 4096, NULL, 1, NULL);

    printf("can create LSO task first\n");
}

void pcf8575_liftTube_spillOil_overHeat_task(void *arg)
{
    enum use_state current_use_state = production_mode;
    use_state_write(current_use_state);
    while (1)
    {
        // 抬起、泄油、超温
        vTaskDelay(500 / portTICK_PERIOD_MS);
        pcf8575_port_read(&pcf8575_LSO, &current_pcf8575_LSO_val);
        if (use_state_read() == demo_mode)
        {
            state = normal;
        }
        else
        {
            // printf("current_pcf8575_LSO_val :%x\n", current_pcf8575_LSO_val);
            switch ((current_pcf8575_LSO_val | 0x1fff))
            {
                case 0xffff:
                    // printf("over heat\n");
                    PID_mode_write(mode_null);
                    state = overHeat;
                    current_pcf8575_LSO_val  |= (1 << pcf8575_OVER_HEAT_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_SPILL_OIL_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_LIFT_TUBE_NUM);
                    pcf8575_port_write(&pcf8575_LSO, current_pcf8575_LSO_val);
                    break;
                case 0x7fff:
                    // printf("spill oil\n");   
                    PID_mode_write(mode_null);
                    state = spillOil;
                    current_pcf8575_LSO_val  |= (1 << pcf8575_OVER_HEAT_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_SPILL_OIL_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_LIFT_TUBE_NUM);
                    pcf8575_port_write(&pcf8575_LSO, current_pcf8575_LSO_val);
                    break;
                case 0x3fff:
                    // printf("lift tube\n");
                    PID_mode_write(mode_null);
                    state = liftTube;
                    current_pcf8575_LSO_val  |= (1 << pcf8575_OVER_HEAT_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_SPILL_OIL_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_LIFT_TUBE_NUM);
                    pcf8575_port_write(&pcf8575_LSO, current_pcf8575_LSO_val);
                    break;
                default:
                    state = normal;
                    current_pcf8575_LSO_val  |= (1 << pcf8575_OVER_HEAT_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_SPILL_OIL_NUM);
                    current_pcf8575_LSO_val  |= (1 << pcf8575_LIFT_TUBE_NUM);
                    pcf8575_port_write(&pcf8575_LSO, current_pcf8575_LSO_val);
                    break;
            }
        }
    }
    
}

void state_use_queue_create(void)
{
    handle_queue_state_use = xQueueCreate(1, sizeof(enum use_state));
}

enum use_state use_state_read(void)
{
    enum use_state current_use_state = demo_mode;
    xQueuePeek(handle_queue_state_use, &current_use_state, 1);
    return current_use_state;
}

// write
void use_state_write(enum use_state current_use_state)
{
    xQueueOverwrite(handle_queue_state_use, &current_use_state);
}

liftTube_spillOil_overHeat_state liftTube_spillOil_overHeat_state_write(void)
{
    liftTube_spillOil_overHeat_state current_state = state;
    return current_state;
}
