/* SPI Master example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#define EDU_SKIDS_J3_SPI_HOST    HSPI_HOST
#define DMA_CHAN    2

#define PIN_NUM_MISO 33
#define PIN_NUM_MOSI 19
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

spi_device_handle_t spi;

void spi_write(spi_device_handle_t spi, const uint8_t *data, int len)
{
    esp_err_t ret = ESP_OK;
    spi_transaction_t t;
    if (len==0) return;             //no need to send anything
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len*8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

void dev_spi_init(void)
{
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=20
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=20*1000,           //Clock out at 20khz
        .mode=0,                                //SPI mode 0
        .spics_io_num=PIN_NUM_CS,               //CS pin
		.flags=SPI_DEVICE_BIT_LSBFIRST,         //LSB, default MSB
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(EDU_SKIDS_J3_SPI_HOST, &buscfg, DMA_CHAN);
    ESP_ERROR_CHECK(ret);
    ret=spi_bus_add_device(EDU_SKIDS_J3_SPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
}

void app_main(void)
{
	unsigned char cnt = 0;

	dev_spi_init();

	while(1) {
		spi_write(spi, &cnt, 1);
		cnt += 1;
        printf("cnt = %d\r\n", cnt);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}
