#include "NTC_thermistor.h"

QueueHandle_t handle_queue_NTC_thermistor;
int width_dec_max = (1 << WIDTH_BIT) - 1;

esp_err_t NTC_thermistor_init(void)
{
    esp_err_t ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
    if (ret == ESP_ERR_NOT_SUPPORTED)
    {
        ESP_LOGW("EFUSE_CHECK", "Calibration scheme not supported, skip software calibration");
    }
    else if (ret == ESP_ERR_INVALID_VERSION)
    {
        ESP_LOGW("EFUSE_CHECK", "eFuse not burnt, skip software calibration");
    }
    else if (ret == ESP_OK)
    {
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
    }
    else
    {
        ESP_LOGE("EFUSE_CHECK", "Invalid arg");
    }

    // ESP ADC Setup
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_12));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11)); /* GPIO1 */

    handle_queue_NTC_thermistor = xQueueCreate(1, sizeof(double));

    xTaskCreate(task_NTC_thermistor_read_temp, "NTCMeasureTask", 1024 * 8, NULL, 2, NULL);

    return ESP_OK;
}

void task_NTC_thermistor_read_temp(void *pvParams)
{
    while (1)
    {
        double temperature_kelvin = 0;
        for (int i = 0; i < CONSTANT_SAMPLING; i++)
        {
            uint32_t raw_voltage = adc1_get_raw(ADC1_CHANNEL_0);
            uint32_t cal_voltage = esp_adc_cal_raw_to_voltage(raw_voltage, &adc1_chars);
            // cal_voltage = 46.423425278354226; //
            temperature_kelvin += temperature_calculation_kelvin(cal_voltage);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        temperature_kelvin /= CONSTANT_SAMPLING;

        // ESP_LOGI("ESP_ADC", "Temperature(kelvin): %.2f K", temperature_kelvin);
        // ESP_LOGI("ESP_ADC", "Temperature(kelvin): %.2f °C", temperature_kelvin - 273.15);
        // ESP_LOGI("ESP_ADC", "Temperature(kelvin): %.2f °F", (temperature_kelvin - 273.15) * 1.800 + 32.00);

        NTC_thermistor_queue_write(temperature_kelvin);
        temperature_kelvin = 0;
        vTaskDelay(SAMPLING_DELAY_MS / portTICK_PERIOD_MS);
    }
}

double temperature_calculation_kelvin(uint32_t calibrated_voltage)
{
    //   ESP_LOGI("ESP_ADC", "cali data: %ld mV", calibrated_voltage);

    double cal_voltage_v = (double)calibrated_voltage / 1000;
    // cal_voltage_v = 0.147;

    // (R2 / (Rt + R2)) * Vs = Vout
    // Rt = ( R2 / (Vout / Vs) - R2 )
    double resistance_voltage_divider_ohm = 4700;                                       // resistance of voltage divider, in ohm
    double resistance_thermistor_ohm = (double)(4700 / (cal_voltage_v / 3.300) - 4700); // resistance of thermistor, in ohm
    // ESP_LOGI("ESP_ADC", "Resistance: %.2f ohm", resistance_thermistor_ohm);
    // printf("Resistance: \n%.2f ohm\n", resistance_thermistor_ohm);

    // float temperature_kelvin_beta = (1 / (1/4066 * log(resistance_thermistor_ohm/98630) + 1/298.15)); // beta model
    // resistance_thermistor_ohm = 329400.0;
    double temperature_kelvin_sh = 1 / (coefficient_A + coefficient_B * log(resistance_thermistor_ohm) + coefficient_C * pow(log(resistance_thermistor_ohm), 3)); // S-H model
    // temperature_kelvin_sh = 453.5;

    return temperature_kelvin_sh;
}

double NTC_thermistor_queue_read(void)
{
    double current_temperature;
    xQueuePeek(handle_queue_NTC_thermistor, &current_temperature, 1);
    return current_temperature;
}

void NTC_thermistor_queue_write(double temperature)
{
    xQueueOverwrite(handle_queue_NTC_thermistor, &temperature);
}
