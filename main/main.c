/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

#include "time.h"
#include "sys/time.h"

#include "wifi_init.h"
#include "usr_sntp.h"
#include "https_request_weather.h"
#include "smart_config.h"
#include "usr_led_strip.h"
#include "usr_aip1638.h"
#include "aht21.h"

#include "usr_lvgl.h"

#define TAG "main"

void disp_update(void)
{
	// 1. 锟斤拷锟斤拷锟斤拷锟�-锟斤拷前时锟戒，实锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷锟斤拷锟轿憋拷锟斤拷
	// #define	_TIME_T_ long
	// typedef	_TIME_T_ time_t;
	time_t now;

	// 2. 锟斤拷锟斤拷锟街凤拷锟斤拷锟斤拷锟斤拷锟节达拷锟斤拷锟斤拷锟斤拷址锟�
	char strftime_buf[64];

	// 3. 锟斤拷锟斤拷锟斤拷锟斤拷锟秸ｏ拷时锟斤拷锟斤拷锟绞绞憋拷锟斤拷锟斤拷
	struct tm timeinfo;

	// 4. 锟斤拷取锟斤拷前时锟戒，锟矫碉拷锟斤拷1970-1-1锟斤拷锟斤拷锟狡碉拷锟斤拷锟斤拷锟�
	// time_t	   time (time_t *_timer);
	// 锟斤拷锟捷ｏ拷1锟斤拷锟斤拷知锟斤拷time_t锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷
	// gettimeofday锟斤拷锟斤拷也锟缴伙拷取锟斤拷前时锟戒，锟矫碉拷锟斤拷锟斤拷timeval锟斤拷锟酵碉拷时锟戒，锟斤拷锟斤拷time_t
	//	struct timeval {
	//		time_t		tv_sec;		/* seconds */
	//		suseconds_t	tv_usec;	/* and microseconds */
	//	};
	// 锟斤拷锟斤拷
	time(&now);

	// Set timezone to China Standard Time
	setenv("TZ", "CST-8", 1);
	tzset();

	// 5. 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷玫锟斤拷锟角帮拷锟绞憋拷洌拷锟斤拷锟斤拷锟�-时锟斤拷锟诫）
	localtime_r(&now, &timeinfo);
	// 6. 锟斤拷锟斤拷锟斤拷锟斤拷转锟斤拷为锟街凤拷锟斤拷
	strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d\n%I:%M:%S", &timeinfo);

	time_update_to_lcd(strftime_buf);


	float temp, humi;
	read_aht21_data(&temp, &humi);
	temp_update_to_lcd(temp);
	humi_update_to_lcd(humi);
}

void usr_task1( void * pvParameters )
{
	for( ;; ){
		disp_update();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void usr_sntp_task( void * pvParameters )
{
	for( ;; ){
		if (0 == wifi_is_connect())
		{
			usr_sntp_init();
		}
		vTaskDelay(30000 / portTICK_PERIOD_MS);
	}
}

void usr_request_weather_task( void * pvParameters )
{
	for( ;; ){
		if (0 == wifi_is_connect())
		{
			https_request_weather();
		}
		vTaskDelay(60000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	// 锟斤拷锟斤拷GUI
	usr_lvgl();

	// 锟教讹拷路锟缴诧拷锟斤拷
	wifi_init();

	// 支锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷煤锟斤拷锟斤拷锟�
//	smart_config();

	// 锟斤拷锟斤拷锟斤拷锟绞�
	aip1638_demo();

	aht21_start();

	// 时锟斤拷同锟斤拷锟斤拷锟斤拷
	xTaskCreate(usr_sntp_task, "usr_sntp_task", 4096, NULL, 5, NULL);
	// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	xTaskCreate(usr_request_weather_task, "usr_request_weather_task", 4096, NULL, 5, NULL);

	xTaskCreate(led_strip_task, "led_strip_task", 4096, NULL, 5, NULL);

	xTaskCreate(usr_task1, "usr_task1", 4096, NULL, 5, NULL);

}
