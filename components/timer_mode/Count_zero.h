#ifndef COUNT_ZERO_H_
#define COUNT_ZERO_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/queue.h"

#define uchar unsigned char
#define uint unsigned int

#define Force_Heat_Over_Delta 3

enum timer_preheat_approve_state
{
    Timer_Preheat_Disapprove,
    Timer_Preheat_Approve,
};

// the state of countdown
enum timer_countdown_state
{
    Timer_Countdown_Stop,  // countdown stop
    Timer_Countdown_Start, // countdown start
};

enum timer_drop_approve_state
{
    Timer_Drop_Disapprove,
    Timer_Drop_Wait_Disapprove,
    Timer_Drop_Approve,
};

enum timer_force_heat_state
{
    Timer_Force_Heat,
    Timer_No_Force_Heat,
};

/**
 * @brief Read rest time of countdown from queue, used for other components.
 * @return Type: int. Value of rest time of countdown.
 */
int menu_read_remaining_countdown(void);

/**
 * @brief Read a state of countdown from queue, used for count_down task.
 * @return Type: enum timer_countdown_state.
 */
enum timer_countdown_state read_countdown_start(void);

/**
 * @brief Write a state of countdown to queue.
 * @param current_countdown_state Type: enum timer_countdown_state.
 */
void write_countdown_start(enum timer_countdown_state current_countdown_state);

/**
 * @brief Write a state of countdown into queue used one time if event trigger.
 * @note if current countdown state is start and event triggers, PID mode is NULL and countdown state is stop.
 */
enum mode_select_state timer_start_button_event(void);

/**
 * @brief Write a stop state of countdown into queue, used for manual components.
 */
void countdown_state_Mailbox_write_stop_for_manual(void);

void countdown_temperature_write_for_ui_events(double current_temperature);

double countdown_temperature_read_for_ui_events(void);

/**
 * @brief Initialize for creating queues of countdown state, countdown rest time and countdown target time and task of countdown.
 */
void countdown_init();

/**
 * @brief countdown task for deal with countdown state, rest time of countdown time and target countdown time.
 */
void countdownTask(void *pvParameters);

/**
 * @brief 自动模式强制加热任务
*/
void timerForceHeatTask(void *pvParameters);

/**
 * @brief Write a target countdown time into queue.
 * @param second type: int. The value of target countdown time.
 */
void count_zero_second_queue_write(int second);

/**
 * @brief Read a countdown target time from queue.
 * @return type: int. The value of target countdown time.
 */
int count_zero_second_queue_read(void);

/**
 * @brief Read rest time of countdown from queue by menu_read_remaining_countdown() and convert time into minute bit.
 * @return Type: int. The value of minute bit of rest countdown time.
 */
int Display_countdown_minute();

/**
 * @brief Read rest time of countdown from queue by menu_read_remaining_countdown() and convert time into second bit.
 * @return Type: int. The value of second bit of rest countdown time.
 */
int Display_countdown_second();

enum timer_preheat_approve_state countdown_approve_state_read(void);

void countdown_approve_state_write(enum timer_preheat_approve_state current_countdown_approve_state);

enum timer_drop_approve_state countdown_drop_approve_read(void);

void countdown_drop_approve_write(enum timer_drop_approve_state current_countdown_drop_approve);

int force_heat_countdown_queue_read(void);

void force_heat_countdown_queue_write(int current_force_heat_countdown);

enum timer_force_heat_state force_heat_state_read(void);

void force_heat_state_write(enum timer_force_heat_state current_force_heat_state);

double timer_real_time_PWM_read(void);

esp_err_t timer_real_time_PWM_write(double current_timer_real_time_PWM);

#endif