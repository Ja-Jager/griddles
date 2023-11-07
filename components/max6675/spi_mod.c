#include "spi_mod.h"

esp_err_t SPI_bus_init(void)
{
	spi_bus_config_t buscfg =
		{
			.miso_io_num = MDIO,
			.sclk_io_num = SCK,
			.quadwp_io_num = -1,
			.quadhd_io_num = -1,
			.max_transfer_sz = (4 * 8)};
	esp_err_t ret_bus = spi_bus_initialize(SPI3_HOST, &buscfg, DMA_CHAN);
	ESP_ERROR_CHECK(ret_bus);
	return ret_bus;
}

spi_device_handle_t SPI_device_init(int CS_A_B)
{
	spi_device_handle_t spi;

	spi_device_interface_config_t devCfg_CSAB =
		{
			.mode = 0,
			.clock_speed_hz = 2 * 1000 * 1000, // original is 2MHz, change to 4.3MHz
			.spics_io_num = CS_A_B,
			.queue_size = 3};
	esp_err_t ret_CS_A_B = spi_bus_add_device(SPI3_HOST, &devCfg_CSAB, &spi);
	ESP_ERROR_CHECK(ret_CS_A_B);

	return spi;
}
