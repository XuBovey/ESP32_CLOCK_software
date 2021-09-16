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

#define AIP1638_SPI_HOST    HSPI_HOST
#define DMA_CHAN    2

#define PIN_NUM_MOSI 25
#define PIN_NUM_CLK  26
#define PIN_NUM_CS   27

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

void aip1638_spi_init(void)
{
    esp_err_t ret;
//    spi_device_handle_t spi;
    spi_bus_config_t buscfg={
        .miso_io_num=-1,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=20
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=800*1000,           //Clock out at 800 MHz
        .mode=3,                                //SPI mode 0
        .spics_io_num=PIN_NUM_CS,               //CS pin
		.flags=SPI_DEVICE_BIT_LSBFIRST,         //LSB, default MSB
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
//        .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(AIP1638_SPI_HOST, &buscfg, DMA_CHAN);
    ESP_ERROR_CHECK(ret);
    ret=spi_bus_add_device(AIP1638_SPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
}

/*******************
1表示LED点亮

bit 7   6   5   4   3   2   1   0
    dp  g   f   e   d   c   b   a   hex flag
    0   0   1   1   1   1   1   1   3F  0
    0   0   0   0   0   1   1   0   06  1
*/
uint8_t seg_font_table[]={0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40, 0x80, 0x7b, 0x39, 0x79, 0x71, 0x76, 0x38, 0x3E};
uint8_t data[17] ={0xC0,0xFF};

void aip1638_usr_buf_write(uint8_t offset, uint8_t seg_font_code)
{
	if(offset >7)
		return;

	for(int i=0; i<8; i++){
		if(seg_font_code&(1<<i)) {
			data[2*i + 1] |= 1<<offset;
		}else {
			data[2*i + 1] &= ~(1<<offset);
		}
	}
}

void aip1638_update(void)
{
	uint8_t cmd = 0;

	// 写现存数据命令
	cmd = 0x40;
	spi_write(spi, &cmd, 1);
	// 写16字节数据
	spi_write(spi, &data, 17);
	// 显示开关
	cmd = 0x8F;
	spi_write(spi, &cmd, 1);
}

void app_main(void)
{
	int cnt = 0;

	aip1638_spi_init();

	while(1) {
		int tmp;
		tmp = cnt;
		for(int i=0; i<8; i++) {
			aip1638_usr_buf_write(i,seg_font_table[tmp%10]);
			tmp = (int)(tmp/10);
		}

		cnt += 1;
		aip1638_update();
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}

}
