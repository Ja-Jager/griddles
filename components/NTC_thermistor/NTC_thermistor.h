#ifndef NTC_THERMISTOR_H_
#define NTC_THERMISTOR_H_
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "math.h"

// ADC Calibration
#if CONFIG_IDF_TARGET_ESP32
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_VREF
#elif CONFIG_IDF_TARGET_ESP32S2
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP
#elif CONFIG_IDF_TARGET_ESP32C3
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP
#elif CONFIG_IDF_TARGET_ESP32S3
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP_FIT
#endif

#define BETA 3950
/** Maximum of the output ADC raw digital reading result,
*** which is 4095 under Single Read mode, 8191 under Continuous Read mode.
*** 2 ^ 12 - 1 = 4095, 2 ^ 13 - 1 = 8191
***/

#define coefficient_A 0.0007207995816
#define coefficient_B 0.0002171490624
#define coefficient_C 0.00000008956835924
#define CONSTANT_SAMPLING 5
#define SAMPLING_DELAY_MS 300

#define WIDTH_BIT 13

static esp_adc_cal_characteristics_t adc1_chars;

/**
 * @brief Initializes the NTC thermistor functionality.
 *
 * This function initializes the NTC thermistor by performing eFuse check and software calibration if supported.
 * It configures the ESP ADC, creates a queue for temperature readings, and creates a task for reading the temperature.
 *
 * @return Returns ESP_OK on success, or an appropriate error code otherwise.
 */
esp_err_t NTC_thermistor_init(void);

/**
 * @brief Reads temperature from NTC thermistor.
 *
 * This function reads temperature from an NTC thermistor using an ADC.
 * The temperature is calculated by sampling the ADC values, converting
 * them to voltage, and then performing a temperature calculation.
 *
 * @param pvParams A pointer to the parameters passed to the task (unused).
 *
 * @return None.
 */
void task_NTC_thermistor_read_temp(void *pvParams);

/**
 * @brief Reads the current temperature value from the NTC thermistor queue.
 *
 * This function retrieves the current temperature value from the NTC thermistor queue without removing it from the queue.
 *
 * @return The current temperature value from the NTC thermistor queue.
 */
double NTC_thermistor_queue_read(void);

/**
 * @brief Writes a temperature value to the NTC thermistor queue.
 *
 * This function overwrites the existing temperature value in the NTC thermistor queue
 * with the provided temperature value.
 *
 * @param temperature The temperature value to be written to the queue.
 *
 * @return None.
 */
void NTC_thermistor_queue_write(double temperature);

/**
 * @brief Perform Steinhart-Hart calculation to convert calibrated voltage to temperature in Kelvin (K).
 *
 * This function uses the Steinhart-Hart equation to calculate the temperature in Kelvin (K) based on the provided
 * calibrated voltage value. The Steinhart-Hart equation is a mathematical model that relates the resistance of the
 * thermistor to its temperature.
 *
 * @param calibrated_voltage The voltage in ADC (after calibration) used in the temperature calculation.
 * @return The temperature in Kelvin (K).
 *
 * @see https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
 */
double temperature_calculation_kelvin(uint32_t calibrated_voltage);

#endif /* MAIN_MAX6675_H_ */
