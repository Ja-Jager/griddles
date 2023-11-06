#include "pcf8575_escalator.h"

i2c_dev_t pcf8575_escalator;
u_int16_t current_pcf8575_escalator_val;
QueueHandle_t Handle_Motor_Left_Right;

void pcf8575_escalator_init(void)
{
    // pcf8575_escalator
    i2cdev_init();
    // Zero device descriptor
    memset(&pcf8575_escalator, 0, sizeof(i2c_dev_t));
    // Init i2c device descriptor
    ESP_ERROR_CHECK(pcf8575_init_desc(&pcf8575_escalator, 0x20, 0, pcf8575_SDA_NUM ,pcf8575_SCL_NUM));

    Handle_Motor_Left_Right = xQueueCreate(1, sizeof(Motor_Left_Right));

    xTaskCreate(pcf8575_escalator_task, "pcf8575_escalator_task", 4096, NULL, 1, NULL);

    printf("can create escalator task last\n");
}

void pcf8575_escalator_task(void* arg)
{
    while(1)
    {   
        vTaskDelay(500 / portTICK_PERIOD_MS);
        pcf8575_port_read(&pcf8575_escalator, &current_pcf8575_escalator_val);
        printf("real_pcf8575_val :%x\n", current_pcf8575_escalator_val);
        if((PID_mode_read() == mode_null))
        {
            // 全升
            printf("motor both null\n");
            current_pcf8575_escalator_val &= ~(1 << pcf8575_ESCALATOR_A_NUM); 
            current_pcf8575_escalator_val |= (1 << pcf8575_ESCALATOR_B_NUM); 
            current_pcf8575_escalator_val &= ~(1 << pcf8575_ESCALATOR_C_NUM); 
            current_pcf8575_escalator_val |= (1 << pcf8575_ESCALATOR_D_NUM); 
            pcf8575_port_write(&pcf8575_escalator, current_pcf8575_escalator_val);
        }
        else
        {
            if((read_manual_drop_approve() == manual_drop_approve) || (countdown_drop_approve_read() == Timer_Drop_Approve))
            {
                if(motor_left_right_queue_read() == motor_left)
                {
                    printf("left motor\n");
                    // pcf8575_port_read(&pcf8575_escalator, &current_pcf8575_escalator_val);
                    // printf("real_pcf8575_val :%x\n", current_pcf8575_escalator_val);
                    current_pcf8575_escalator_val |= (1 << pcf8575_ESCALATOR_A_NUM); 
                    current_pcf8575_escalator_val &= ~(1 << pcf8575_ESCALATOR_B_NUM);
                    pcf8575_port_write(&pcf8575_escalator, current_pcf8575_escalator_val);
                }
                else if(motor_left_right_queue_read() == motor_right)
                {
                    printf("right motor\n");
                    current_pcf8575_escalator_val |= (1 << pcf8575_ESCALATOR_C_NUM); 
                    current_pcf8575_escalator_val &= ~(1 << pcf8575_ESCALATOR_D_NUM);
                    pcf8575_port_write(&pcf8575_escalator, current_pcf8575_escalator_val);
                }
                else
                {
                    printf("both motor\n");
                    current_pcf8575_escalator_val |= (1 << pcf8575_ESCALATOR_A_NUM); 
                    current_pcf8575_escalator_val &= ~(1 << pcf8575_ESCALATOR_B_NUM);
                    current_pcf8575_escalator_val |= (1 << pcf8575_ESCALATOR_C_NUM); 
                    current_pcf8575_escalator_val &= ~(1 << pcf8575_ESCALATOR_D_NUM);
                    pcf8575_port_write(&pcf8575_escalator, current_pcf8575_escalator_val);
                }
            }
        }
    }
}

Motor_Left_Right motor_left_right_queue_read(void)
{
    Motor_Left_Right current_motor_left_right = motor_left;
    xQueuePeek(Handle_Motor_Left_Right, &current_motor_left_right, 1);
    return current_motor_left_right;
}

void motor_left_right_queue_write(Motor_Left_Right current_motor_left_right)
{
    xQueueOverwrite(Handle_Motor_Left_Right, &current_motor_left_right);
}
