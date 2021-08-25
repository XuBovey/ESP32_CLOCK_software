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

#define TAG "main"

void time_test(void)
{
	// 1. �������-��ǰʱ�䣬ʵ������һ�������α���
	// #define	_TIME_T_ long
	// typedef	_TIME_T_ time_t;
	time_t now;

	// 2. �����ַ��������ڴ�������ַ�
	char strftime_buf[64];

	// 3. ���������գ�ʱ�����ʽʱ�����
	struct tm timeinfo;

	// 4. ��ȡ��ǰʱ�䣬�õ���1970-1-1�����Ƶ������
	// time_t	   time (time_t *_timer);
	// ���ݣ�1����֪��time_t��һ��������
	// gettimeofday����Ҳ�ɻ�ȡ��ǰʱ�䣬�õ�����timeval���͵�ʱ�䣬����time_t
	//	struct timeval {
	//		time_t		tv_sec;		/* seconds */
	//		suseconds_t	tv_usec;	/* and microseconds */
	//	};
	// ����
	time(&now);

	// Set timezone to China Standard Time
	setenv("TZ", "CST-8", 1);
	tzset();

	// 5. ����������õ���ǰ��ʱ�䣨������-ʱ���룩
	localtime_r(&now, &timeinfo);
	// 6. ��������ת��Ϊ�ַ���
	strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
	// 7. �������ݴӴ������
	ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
#if 0
	// 8. �޸�ʱ��
	timeinfo.tm_hour += 1;
	// 9. ʱ���ʽת��
	now = mktime(&timeinfo);
	// 10. ����ʱ��
	struct timeval tv_now = {now,0};
	settimeofday(&tv_now, NULL);

	// 11. �ٴλ�ȡ����ӡʱ��
	time(&now);
	localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "Date:%Y-%m-%d Time:%I:%M:%S", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: \n%s\n", strftime_buf);
#endif
}

void usr_task1( void * pvParameters )
{
	for( ;; ){
		time_test();
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
	// �̶�·�ɲ���
	wifi_init();

	// ֧��������������ú�����
//	smart_config();

	xTaskCreate(usr_sntp_task, "usr_sntp_task", 4096, NULL, 5, NULL);
	xTaskCreate(usr_request_weather_task, "usr_request_weather_task", 4096, NULL, 5, NULL);
	xTaskCreate(usr_task1, "usr_task1", 4096, NULL, 5, NULL);
	xTaskCreate(led_strip_task, "led_strip_task", 4096, NULL, 5, NULL);
}
