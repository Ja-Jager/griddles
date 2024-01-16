#include "buzzer.h"

const uint16_t notes[]  ={
    0,31,33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,87,93,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,
    233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,
    1760,1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186,4435,4699,4978};

ledc_timer_config_t ledc_timer;
ledc_channel_config_t ledc_channel;

QueueHandle_t handle_queue_buzzer_occasion;

// buzzer_structure_t buzzer_set;

void buzzer_init(void)
{
    ledc_timer.duty_resolution = BUZZER_TIMER_DUTY_RES;    // resolution of PWM duty
    ledc_timer.freq_hz = notes[BUZZER_TIMER_FREQ_DEFAULT_KEY_NUM];  // frequency of PWM signal, max:5000, when resolution is 13 bits.
    ledc_timer.speed_mode = BUZZER_TIMER_SPEED_MODE;            //  timermode
    ledc_timer.timer_num = BUZZER_TIMER_SOURCE;            // timer index

    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);

    ledc_channel.channel    = BUZZER_CHANNEL_NUM;
    ledc_channel.duty       = BUZZER_CHANNEL_DEFAULT_DUTY;
    ledc_channel.gpio_num   = BUZZER_CHANNEL_GPIO_NUM;
    ledc_channel.speed_mode = BUZZER_CHANNEL_SPEED_MODE;
    ledc_channel.hpoint     = BUZZER_CHANNEL_HPOINT;
    ledc_channel.timer_sel  = BUZZER_CHANNEL_TIMER_SOURCE;

    ledc_channel_config(&ledc_channel);

    handle_queue_buzzer_occasion = xQueueCreate(1, sizeof(enum buzzer_occasion_select));
    xTaskCreate(task_buzzer, " buzzerTask", 1024 * 8, NULL, 2, NULL);
}

void task_buzzer(void *arg)
{
    enum buzzer_occasion_select current_buzzer_occasion = buzzer_null;
    buzzer_occasion_queue_write(current_buzzer_occasion);
    while(1)
    {
        current_buzzer_occasion = buzzer_occasion_queue_read();
        if(current_buzzer_occasion == buzzer_countdown_over)
        {
            buzzer_countdown_over_function();
            buzzer_occasion_queue_write(buzzer_null);
        }
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

void buzzer(piano_note_t current_note, uint32_t current_loudness, float loud_time, float no_loud_time, uint8_t loud_cycle_time)
{
    uint8_t current_loud_cycle_time = 0;
    ledc_set_freq(BUZZER_TIMER_SPEED_MODE, BUZZER_TIMER_SOURCE, notes[current_note]);
    for(current_loud_cycle_time = 0; current_loud_cycle_time < loud_cycle_time; current_loud_cycle_time++)
    {
        ledc_set_duty(BUZZER_TIMER_SPEED_MODE, BUZZER_CHANNEL_NUM, current_loudness);
        ledc_update_duty(BUZZER_TIMER_SPEED_MODE, BUZZER_CHANNEL_NUM);
        vTaskDelay((1000 * loud_time) / portTICK_PERIOD_MS);

        ledc_set_duty(BUZZER_TIMER_SPEED_MODE, BUZZER_CHANNEL_NUM, 0);
        ledc_update_duty(BUZZER_TIMER_SPEED_MODE, BUZZER_CHANNEL_NUM);
        vTaskDelay((1000 * no_loud_time) / portTICK_PERIOD_MS);
    }
}

enum buzzer_occasion_select buzzer_occasion_queue_read(void)
{
    enum buzzer_occasion_select current_buzzer_occasion = buzzer_null;
    xQueuePeek(handle_queue_buzzer_occasion, &current_buzzer_occasion, 1);
    return current_buzzer_occasion;
}

esp_err_t buzzer_occasion_queue_write(enum buzzer_occasion_select current_buzzer_occasion)
{
    xQueueOverwrite(handle_queue_buzzer_occasion, &current_buzzer_occasion);
    return ESP_OK;
}

void buzzer_countdown_over_function(void)
{
    buzzer(NOTE_G4, 7168, 1, 1, 2);
}

// void buzzer_drop_approve_function(void)
// {
//     buzzer(NOTE_G4, 7168, 1, 1, 1);
// }
