#include "softpwm.h"

void softPwmSetup(softPwm_t *softpwm)
{
    gpio_set_direction((gpio_num_t)softpwm->PWMPin, GPIO_MODE_OUTPUT);
}

void softpwm_init(softPwm_t *softpwm)
{
    xTaskCreate(task_softpwm, "softpwmTask", 1024 * 8, softpwm, 2, NULL);
}

void task_softpwm(void *arg)
{
    softPwm_t softpwm = *(softPwm_t *)arg;
    softPwmSetup(&softpwm);
    while (1)
    {
        softpwm.dutypercent = (int)round(PID_queue_read() / 25.5);
        printf("%d\n", softpwm.dutypercent);
        for (size_t i = 0; i < (int)softpwm.dutypercent; i++)
        {
            gpio_set_level((gpio_num_t)softpwm.PWMPin, 1);
            vTaskDelay(1000 / (int)(softpwm.freq * 10) / portTICK_PERIOD_MS); // 周期5s
        }
        for (size_t i = 0; i < 10 - (int)softpwm.dutypercent; i++)
        {
            gpio_set_level((gpio_num_t)softpwm.PWMPin, 0);
            vTaskDelay(1000 / (int)(softpwm.freq * 10) / portTICK_PERIOD_MS);
        }
    }
}
