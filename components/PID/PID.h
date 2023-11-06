#ifndef PID_H_
#define PID_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "NTC_thermistor.h"
#include "math.h"
#include "Count_zero.h"

#define Duty_MAX 255 // 0 to 255, 2^8 - 1
#define Duty_MIN 0   // 255*0%
#define Duty_Melt 77 // 255*30%

#define SumError_threshold 500.0 // 阈值

#define Proportion_Coefficient 8.9 // 比例系数
#define Integral_Coefficient 0.06    // 积分系数
#define Derivative_Coefficient 64  // 微分系数

#define Umin_range 25             // 死区
#define Melt_Temperature 80  // 油融化区

typedef struct
{
    double SetTemperature; // 目标温度 Desired value
    double Proportion;     // 比例常数 Proportional Const
    double Integral;       // 积分常数 Integral Const
    double Derivative;     // 微分常数 Derivative Const
    int umin;             // 死区低
    double LastError;      // Error[-1]
    double PrevError;      // Error[-2]
    double FirstError;     // Error[-2]
    double SumError;       // Sums of Errors
} PID_structure;

enum mode_select_state
{
    mode_null,   // 无操作
    mode_timer,  // 定时操作
    mode_manual, // 手动操作
};

/**
 *@brief set default values in structure above, create queue and PID calculate task
 */
void PID_calculate_init(void);

// unsigned char pid_calc(PID *pp, int CurrentTemperature);fr
void task_pid_calculate(void *); // PID算法任务

// API接口
esp_err_t PID_queue_init(void);

/**
 * @brief Read(peek) PID duty queue
 * @return 0 <= duty cycle <= 255
 */
int PID_queue_read(void);

/**
 * @brief Write PID duty queue
 * @param duty PID calculated duty cycle
 * @return ESP error code
 */
esp_err_t PID_queue_write(int duty);

/**
 * @brief read PID setting temperature from queue
 * @return setting temperature value
 */
double PID_set_temperature_read(void);

/**
 * @brief write PID setting temperature to queue
 * @param set_temperature value needed to write into queue from ui_events.c
 * @return ESP error code
 */
esp_err_t PID_set_temperature_write(double set_temperature);

/**
 * @brief Read PID mode, return mode_null, mode_timer or mode_manual.
 * @return Type: enum mode_select_state. PID state.
 */
enum mode_select_state PID_mode_read(void);

/**
 * @brief Write a mode state to PID from manual_mode.c or count_zero.c
 * @param mode_state value neededto write into queue from manual_mode.c or count_zero.c
 * @return ESP error code
 */
esp_err_t PID_mode_write(enum mode_select_state mode_state);

#endif
