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

#define TAG "HELLO_WORLD_TEST"

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

void app_main(void)
{
	wifi_init();

	if (0 == wifi_is_connect())
	{
		usr_sntp_init();
		https_request_weather();
	}

#if 0
	ESP_LOGI(TAG, "ESP_LOGI I am xxx \n");
    printf("Hello world! I am xxx \n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
#endif

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        time_test();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
