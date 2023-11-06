#include "NTC_thermistor.h"

adc_oneshot_unit_handle_t adc1_handle;
adc_cali_handle_t adc1_cali_handle = NULL;
const static char *TAG = "ADC";
QueueHandle_t handle_queue_NTC_thermistor;

esp_err_t NTC_thermistor_init(adc_unit_t current_unit_id, enum adc_channel_t current_adc_channel, int *demo_offset)
{
 
   adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = current_unit_id,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_11
    };
  ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, current_adc_channel, &config));
 
  example_adc_calibration_init(current_unit_id, ADC_ATTEN_DB_11, &adc1_cali_handle);

  handle_queue_NTC_thermistor = xQueueCreate(1, sizeof(double));

  xTaskCreate(task_NTC_thermistor_read_temp, "NTCMeasureTask", 1024 * 8, (void *)demo_offset, 2, NULL);

  return ESP_OK;
}

void task_NTC_thermistor_read_temp(void *pvParams)
{
  while (1)
  {

    double temperature_kelvin = 0;
    for (int i = 0; i < CONFIG_CONSTANT_SAMPLING; i++)
    {
      int raw_voltage=0,cal_voltage=0;
      adc_oneshot_read(adc1_handle,ADC_CHANNEL_0,&raw_voltage);
      adc_cali_raw_to_voltage(adc1_cali_handle,raw_voltage,&cal_voltage);
      temperature_kelvin += temperature_calculation_kelvin(cal_voltage);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    temperature_kelvin /= CONFIG_CONSTANT_SAMPLING;
    temperature_kelvin += *(int *)pvParams;
    
    // ESP_LOGI("ESP_ADC", "Temperature(kelvin): %.2f K", temperature_kelvin);
    // ESP_LOGI("ESP_ADC", "Temperature(kelvin): %.2f °C", temperature_kelvin - 273.15);
    // ESP_LOGI("ESP_ADC", "Temperature(kelvin): %.2f °F", (temperature_kelvin - 273.15) * 1.800 + 32.00);

    NTC_thermistor_queue_write(temperature_kelvin);
    temperature_kelvin = 0;
    vTaskDelay(CONFIG_SAMPLING_DELAY/ portTICK_PERIOD_MS);
  }
}

double temperature_calculation_kelvin(uint32_t calibrated_voltage)
{
  // ESP_LOGI("ESP_ADC", "cali data: %d mV", calibrated_voltage);

  double cal_voltage_v = (double)calibrated_voltage / 1000;

  // (R2 / (Rt + R2)) * Vs = Vout
  // Rt = ( R2 / (Vout / Vs) - R2 )
  double resistance_voltage_divider_ohm = CONFIG_RESISTANCE_VOLTAGE_DIVIDER_OHM;                                    // resistance of voltage divider, in ohm
  // play with "." vs. "," to see why this might be your problem
  char * input1 = CONFIG_EXP_VOLTAGE;
  // will take a pointer beyond the last character parsed
  char * end_ptr1;
  // convert
  float result_CONFIG_EXP_VOLTAGE = strtof( input1, &end_ptr1 );
  double resistance_thermistor_ohm = (double)(CONFIG_RESISTANCE_VOLTAGE_DIVIDER_OHM / (3.3 / result_CONFIG_EXP_VOLTAGE) - CONFIG_RESISTANCE_VOLTAGE_DIVIDER_OHM); // resistance of thermistor, in ohm
  // ESP_LOGI("ESP_ADC", "Resistance: %.2f ohm", resistance_thermistor_ohm);
  // printf("Resistance: \n%.2f ohm\n", resistance_thermistor_ohm);
  // play with "." vs. "," to see why this might be your problem
  char * input2 = COEFFICIENT_A;
  char * input3 = COEFFICIENT_B;
  char * input4 = COEFFICIENT_C;
  // will take a pointer beyond the last character parsed
  char * end_ptr2,end_ptr3,end_ptr4;
  // convert
  float result_COEFFICIENT_A; = strtof( input2, &end_ptr2 );
  float result_COEFFICIENT_B; = strtof( input3, &end_ptr3 );
  float result_COEFFICIENT_C; = strtof( input4, &end_ptr4 );
  // float temperature_kelvin_beta = (1 / (1/4066 * log(resistance_thermistor_ohm/98630) + 1/298.15)); // beta model
  double temperature_kelvin_sh = 1 / (result_COEFFICIENT_A + result_COEFFICIENT_B * log(resistance_thermistor_ohm) + result_COEFFICIENT_C * pow(log(resistance_thermistor_ohm), 3)); // S-H model

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

bool example_adc_calibration_init(adc_unit_t unit, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE(TAG, "Invalid arg or no memory");
    }

    return calibrated;
}