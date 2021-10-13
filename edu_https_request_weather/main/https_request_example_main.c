/* HTTPS GET Example using plain mbedTLS sockets
 *
 * Contacts the howsmyssl.com API via TLS v1.2 and reads a JSON
 * response.
 *
 * Adapted from the ssl_client1 example in mbedtls.
 *
 * Original Copyright (C) 2006-2016, ARM Limited, All Rights Reserved, Apache 2.0 License.
 * Additions Copyright (C) Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD, Apache 2.0 License.
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "esp_tls.h"
#include "esp_crt_bundle.h"

/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "api.seniverse.com"
#define WEB_PORT "80"
#define WEB_URL_BEIJING "https://api.seniverse.com/v3/weather/daily.json?key=S-7cD41DQtD2xRQFm&location=beijing&language=en&unit=c&start=0&days=5"
#define WEB_URL_SHANGHAI "https://api.seniverse.com/v3/weather/daily.json?key=S-7cD41DQtD2xRQFm&location=shanghai&language=en&unit=c&start=0&days=5"
#define WEB_HOST "https://api.seniverse.com"


static const char *TAG = "example";

static const char REQUEST_BEIJING[] = "GET " WEB_URL_BEIJING " \r\n\r\n";

static const char REQUEST_SHANGHAI[] = "GET " WEB_URL_SHANGHAI "\r\n\r\n";

//static const char REQUEST_BEIJING[] = "GET " WEB_URL_BEIJING " HTTP/1.1\r\n"
//                             "Host: "WEB_SERVER"\r\n"
//							 "Connection: close\r\n"
//                             "\r\n";
//
//static const char REQUEST_SHANGHAI[] = "GET " WEB_URL_SHANGHAI " HTTP/1.1\r\n"
//                             "Host: "WEB_SERVER"\r\n"
//							 "Connection: close\r\n"
//                             "\r\n";

static void https_get_request(esp_tls_cfg_t cfg, int city)
{
    char buf[512];
    int ret, len;

    struct esp_tls *tls = esp_tls_conn_http_new(WEB_HOST, &cfg);

    if (tls != NULL) {
        ESP_LOGI(TAG, "Connection established...");
    } else {
        ESP_LOGE(TAG, "Connection failed...");
        goto exit;
    }

    size_t written_bytes = 0;
    size_t req_data_len = 0;
    if (1 == city) {
    	req_data_len = sizeof(REQUEST_SHANGHAI);
    }else {
    	req_data_len = sizeof(REQUEST_BEIJING);
    }
    do {
    	if (1 == city) {
			ret = esp_tls_conn_write(tls,
									 REQUEST_SHANGHAI + written_bytes,
									 sizeof(REQUEST_SHANGHAI) - written_bytes);
    	}else {
    		ret = esp_tls_conn_write(tls,
									 REQUEST_BEIJING + written_bytes,
									 sizeof(REQUEST_BEIJING) - written_bytes);
    	}

        if (ret >= 0) {
            ESP_LOGI(TAG, "%d bytes written", ret);
            written_bytes += ret;
        } else if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
            ESP_LOGE(TAG, "esp_tls_conn_write  returned: [0x%02X](%s)", ret, esp_err_to_name(ret));
            goto exit;
        }
    } while (written_bytes < req_data_len);

    ESP_LOGI(TAG, "Reading HTTP response...");

    do {
        len = sizeof(buf) - 1;
        bzero(buf, sizeof(buf));
        ret = esp_tls_conn_read(tls, (char *)buf, len);

        if (ret == ESP_TLS_ERR_SSL_WANT_WRITE  || ret == ESP_TLS_ERR_SSL_WANT_READ) {
            continue;
        }

        if (ret < 0) {
            ESP_LOGE(TAG, "esp_tls_conn_read  returned [-0x%02X](%s)", -ret, esp_err_to_name(ret));
            break;
        }

        if (ret == 0) {
            ESP_LOGI(TAG, "connection closed");
            break;
        }

        len = ret;
        ESP_LOGD(TAG, "%d bytes read", len);
        /* Print response directly to stdout as it is read */
        for (int i = 0; i < len; i++) {
            putchar(buf[i]);
        }
        putchar('\n'); // JSON output doesn't have a newline at end
    } while (1);

exit:
    esp_tls_conn_delete(tls);
    for (int countdown = 10; countdown >= 0; countdown--) {
        ESP_LOGI(TAG, "%d...", countdown);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void https_request_task(void *pvparameters)
{
    ESP_LOGI(TAG, "Start https_request example");

    esp_tls_cfg_t cfg = {
        .crt_bundle_attach = esp_crt_bundle_attach,
    };
    https_get_request(cfg, 0);
    https_get_request(cfg, 1);

    ESP_LOGI(TAG, "Finish https_request example");
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(&https_request_task, "https_get_task", 8192, NULL, 5, NULL);
}
