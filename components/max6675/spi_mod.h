#ifndef _spi_mod_h
#define _spi_mod_h

#define DMA_CHAN SPI_DMA_CH_AUTO

#define MDIO 1
#define SCK 16
#define CSA 15

#define PIN_NUM_DC 26
#define PIN_NUM_RST 27
#define PIN_NUM_BCKL 28

#include "driver/spi_master.h"

// spi_device_handle_t spi_init(int CS_A_B, spi_host_device_t SPI_2_3_HOST);
esp_err_t SPI_bus_init(void);
spi_device_handle_t SPI_device_init(int);

#endif
