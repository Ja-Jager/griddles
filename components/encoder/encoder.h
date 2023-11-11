#ifndef __MY_ENCODER_H
#define __MY_ENCODER_H

#include "rotary_encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/queue.h"
#include "manual_mode.h"
#include "Count_zero.h"

/**
 * @brief Enumeration for key states.
 */
typedef enum key_state
{
    KEY_UP = 0, /**< 编码器按键弹起状态. Encoder key up state. */
    KEY_DOWN    /**< 编码器按键按下状态. Encoder key down state. */
} key_state_t;

/**
 * @brief Enumeration representing button modes.
 */
// typedef enum button_mode
// {
//     BUTTON_MANUAL_MODE = 0,         /**< 编码器按键弹起状态. Manual mode */
//     BUTTON_AUTO_MODE,               /**< 编码器按键按下状态. Auto mode */
//     BUTTON_MANUAL_READY_MODE,       /**< Manual ready mode */
//     BUTTON_AUTO_READY_MODE,         /**< Auto ready mode */
// } button_mode_t;

#define ENCODER_A_PIN 5                                     /* 编码器A端 */
#define ENCODER_B_PIN 6                                     /* 编码器B端 */
// #define ENCODER_PUSH_PIN 14                                  /* 编码器KEY端 */

/**
 * @brief 编码器 KEY GPIO bit 掩码. Encoder KEY GPIO bit mask for selection.
 *
 * This macro defines the GPIO bit mask for selecting the encoder key.
 * The ENCODER_PUSH_GPIO_PIN_SEL macro is calculated as (1ULL << ENCODER_PUSH_PIN).
 * It is used to mask a specific bit in the GPIO register to manipulate the encoder key.
 *
 * @see ENCODER_PUSH_PIN
 */
// #define ENCODER_PUSH_GPIO_PIN_SEL (1ULL << ENCODER_PUSH_PIN)

#define MODE_CHANGE_TO_MANUAL 0
#define MODE_CHANGE_TO_AUTO 1

/**
 * @brief Configures the encoder.
 *
 * This function configures the encoder by setting up the necessary GPIO pins, creating a mutex,
 * and configuring the encoder A and B pins. It also sets the glitch filter and starts the encoder.
 *
 * @return None.
 */
void encoder_config(void);      /* 编码器配置 */

/**
 * @brief Creates the input task.
 *
 * This function creates the input task by calling the `xTaskCreatePinnedToCore` function.
 * The input task is responsible for executing the `encoder_task` function. It assigns a name
 * to the task ("input task"), sets the stack size to 8 KB, and doesn't pass any parameters (`NULL`).
 * The priority of the task is set to 1, and the task is created on core 1.
 *
 * @return None.
 */
void input_task_create(void);   /* 编码器任务创建 */

/**
 * @brief Retrieves the encoder difference value.
 *
 * This function retrieves the encoder difference value, which represents the difference
 * between the current and previous encoder counts. It returns the difference value as
 * a signed 32-bit integer.
 *
 * @return The encoder difference value.
 */
int32_t encoder_get_diff(void); /* 获取编码器值 */

/**
 * @brief Retrieves the state of the encoder push button.
 *
 * This function retrieves the state of the encoder push button. If the button is currently pressed
 * (KEY_DOWN), it disables reading the encoder difference value and returns true. Otherwise, it enables
 * reading the encoder difference value and returns false.
 *
 * @return The state of the encoder push button (true if pressed, false otherwise).
 */
bool encoder_get_is_push(void); /* 获取编码器KEY是否按下值 */

/**
 * @brief Reads the value from the Encoder mailbox queue.
 *
 * This function reads the value from the Encoder mailbox queue without removing it from the queue.
 * It retrieves the value from the `Encoder_Mailbox` queue and stores it in the `cnt` variable.
 * The function then returns the value stored in `cnt`.
 *
 * @return The value read from the Encoder mailbox queue.
 */
int Encoder_queue_read(void);

/**
 * @brief Writes the encoder count to the encoder mailbox queue.
 *
 * This function writes the encoder count value to the encoder mailbox queue.
 * The count is passed as the `cnt` parameter and is stored in the `Encoder_Mailbox` queue.
 *
 * @param cnt The encoder count value to be written.
 * @return None.
 */
void Encoder_queue_write(int cnt);

/**
 * @brief Initializes the encoder queues and pins.
 *
 * This function initializes the encoder queues and pins by creating queues for mailbox, mode change,
 * and manual target temperature. It also sets up the necessary pins for the HC165 encoder and
 * calls the initialization function for the 74HC165 shift register.
 *
 * @return None.
 */
void encoder_queue_init();

/**
 * @brief Reads the current temperature value from the encoder temperature queue.
 *
 * This function reads the current temperature value from the encoder temperature queue
 * by peeking into the queue without removing the value. The temperature value is returned
 * as a long integer.
 *
 * @return The current temperature value from the encoder temperature queue.
 */
long Encoder_temperature_queue_read(void);

/**
 * @brief Writes the current temperature to the encoder temperature queue.
 *
 * This function writes the current temperature to the encoder temperature queue.
 * It overwrites the existing value in the queue with the provided current temperature.
 *
 * @param current_temperature The current temperature value to be written.
 * @return None.
 */
void Encoder_temperature_queue_write(long current_temperature);

// /**
//  * @brief 读模式切换状态. Retrieves the mode change button state.
//  *
//  * This function retrieves the mode change button state by peeking into the `Handle_Mode_Change`
//  * queue. It reads the current mode from the queue and returns it.
//  *
//  * @return The current mode change button state.
//  */
// button_mode_t Mode_change_button_read(void); 

// /**
//  * @brief 写模式切换状态. Writes the current mode change button state.
//  *
//  * This function writes the current mode change button state to the `Handle_Mode_Change` queue.
//  * It overwrites the previous value in the queue with the current mode value.
//  *
//  * @param current_mode The current mode change button state to be written.
//  * @return None.
//  */
// void Mode_change_button_write(button_mode_t current_mode); 

#endif // ENCODER_H