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
	// 1. 定义变量-当前时间，实际上是一个长整形变量
	// #define	_TIME_T_ long
	// typedef	_TIME_T_ time_t;
	time_t now;

	// 2. 定义字符数组用于存放日期字符
	char strftime_buf[64];

	// 3. 定义年月日，时分秒格式时间变量
	struct tm timeinfo;

	// 4. 获取当前时间，得到从1970-1-1到限制的秒计数
	// time_t	   time (time_t *_timer);
	// 根据（1）中知道time_t是一个长整形
	// gettimeofday函数也可获取当前时间，得到的是timeval类型的时间，包含time_t
	//	struct timeval {
	//		time_t		tv_sec;		/* seconds */
	//		suseconds_t	tv_usec;	/* and microseconds */
	//	};
	// 所以
	time(&now);

	// Set timezone to China Standard Time
	setenv("TZ", "CST-8", 1);
	tzset();

	// 5. 根据秒计数得到当前的时间（年月日-时分秒）
	localtime_r(&now, &timeinfo);
	// 6. 将年月日转换为字符串
	strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
	// 7. 日期数据从串口输出
	ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
#if 0
	// 8. 修改时间
	timeinfo.tm_hour += 1;
	// 9. 时间格式转换
	now = mktime(&timeinfo);
	// 10. 设置时间
	struct timeval tv_now = {now,0};
	settimeofday(&tv_now, NULL);

	// 11. 再次获取并打印时间
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
