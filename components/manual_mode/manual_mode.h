#ifndef MANUAL_MODE_H_
#define MANUAL_MODE_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/queue.h"
#include "PID.h"


#define uchar unsigned char
#define uint unsigned int

enum manual_countdown_state {
    manual_countdown_stop,          // 手动操作结束
    manual_countdown_start,         // 手动操作开始
};

enum manual_preheat_approve_state
{
    manual_preheat_disapprove,
    manual_preheat_approve,
};

enum manual_drop_approve_state
{
    manual_drop_disapprove,
    manual_drop_wait_approve,
    manual_drop_approve,
};

// /**
//  * @brief manual task
//  * @note a task operate the queue handle manual_start_state_Mailbox to contorl manual mode for heating 
// */
// void manual_mode_Task(void *pvParam);

/**
 * @brief Initialize to create task and queue
*/
void manual_mode_init(); 

/**
 * @brief control manual heating stop or start if the manual start event triggers 
 * @note Don't write a parameter.e.g. if manual heating starts and the event triggers, the state turns to stop.
*/
enum mode_select_state manual_mode_start_mailbox_write(void);

void manual_mode_start_mailbox_write_stop_for_countdown(void);

/**
 * @brief Read the manual heating state and return a manual state.
 * @return type: enum manual_countdown_state.
*/
enum manual_countdown_state manual_mode_start_mailbox_read(void);

int manual_countdown_time_read(void);

void manual_countdown_time_write(int current_time);

int manual_countdown_rest_time_read(void);

void manual_countdown_rest_time_write(int current_rest_time);

int manual_countdown_rest_time_minute(int current_rest_time);

int manual_countdown_rest_time_second(int current_rest_time);
// char *manual_countdown_rest_time_convert_to_string(int current_rest_time);

enum manual_preheat_approve_state read_manual_approve_state(void);

void write_manual_approve_state(enum manual_preheat_approve_state current_manual_approve_state);

enum manual_drop_approve_state read_manual_drop_approve(void);

void write_manual_drop_approve(enum manual_drop_approve_state current_manual_drop_approve);

#endif
