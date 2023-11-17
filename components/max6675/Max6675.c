#include "MAX6675.h"
#include "driver/spi_master.h"
#include <driver/gpio.h>
#include "spi_mod.h"
#include "nvs_component.h"

QueueHandle_t Main_temperature_Mailbox; // 主发热管温度
QueueHandle_t Main_temperature_calibration_Mailbox; // 主发热管温度
TaskHandle_t xHandle_main = NULL; // 主发热管传参
double Max6675_Read_Main = 0;        /* 主电热丝 Max6675温度 */

/*——————————————————————————————
 * 函数名称：temp_main_task
 * 函数作用：输出主发热管检测温度
 * 函数输入：无输入
 * 函数输出：无输出
 * 创建时间：2022/12/19
 ——————————————————————————————*/

void temp_main_task(void *pvParams) // 主发热管温度检测任务
{
    NTC_thermistor_queue_write(295.15);
    int temp_calibration = 0;
    if(nvs_read_i8("Calibration", &temp_calibration) == ESP_ERR_NVS_NOT_FOUND)
    {
        nvs_write_i8("Calibration", 0);
    }
    if(temp_calibration > 127)
    {
        temp_calibration = temp_calibration - 256;
    }
    // printf("temp_calibration = %d\n", temp_calibration);
    NTC_thermistor_calibration_queue_write(temp_calibration);

    spi_device_handle_t spi = (spi_device_handle_t)pvParams;
    uint16_t data;

    spi_transaction_t tM =
        {
            .tx_buffer = NULL,
            .rx_buffer = &data,
            .length = 16,
            .rxlength = 16};
    while (1)
    {
        spi_device_acquire_bus(spi, portMAX_DELAY);
        spi_device_transmit(spi, &tM);
        spi_device_release_bus(spi);

        int16_t res = (int16_t)SPI_SWAP_DATA_RX(data, 16);

        if (res & (1 << 2))
        {
              ESP_LOGE(MAX6675_TAG, "Sensor is not connected\n");
        }
        else
        {
            res >>= 3;
            Max6675_Read_Main = res * 0.25;
            Max6675_Read_Main = Max6675_Read_Main + 273.15;
            NTC_thermistor_queue_write(Max6675_Read_Main + (double)(NTC_thermistor_calibration_queue_read()));
            // ESP_LOGI(MAX6675_TAG, "SPI res = %d main_temp = %f\n", res,res * 0.25);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*——————————————————————————————
 * 函数名称：Max6675_init
 * 函数作用：初始化 Max6675 相关引脚，spi总线，设备任务配置
 * 函数输入：无输入
 * 函数输出：无输出
 * 创建时间：2022/12/19
 ——————————————————————————————*/
void Max6675_init(void)
{
    Main_temperature_Mailbox = xQueueCreate(1, sizeof(double));
    Main_temperature_calibration_Mailbox = xQueueCreate(1, sizeof(int));

    TEM_CSA_OUT;
    TEM_SCK_OUT;
    TEM_MDIO_IN;
    TEM_MDIO_PULL;
    SPI_bus_init();
    spi_device_handle_t spi_CSA = SPI_device_init(CSA);
    xTaskCreate(temp_main_task, "temperature_main_task", 1024*8, spi_CSA, 1, &xHandle_main);
}

void NTC_thermistor_queue_write(double temperature)
{
    xQueueOverwrite(Main_temperature_Mailbox, &temperature);
}
double NTC_thermistor_queue_read(void) // 从队列读
{
    double Main_temperature;
    xQueuePeek(Main_temperature_Mailbox, &Main_temperature, 0);
    return Main_temperature;
}

void NTC_thermistor_calibration_queue_write(int calibration_value)
{
    xQueueOverwrite(Main_temperature_calibration_Mailbox, &calibration_value);
}

int NTC_thermistor_calibration_queue_read(void)
{
    int calibration_value;
    xQueuePeek(Main_temperature_calibration_Mailbox, &calibration_value, 0);
    return calibration_value;
}
