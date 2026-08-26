#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "nvs_flash.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Custom classes
#include "Beacon/Beacon.hpp"
#include "TCPShell/TCPShell.hpp"


// --------------------------------------------------
// Global objects
// --------------------------------------------------

Beacon beacon;
Battery battery;

static const char *TAG = "ROTH";


// --------------------------------------------------
// Wi-Fi event handler
// --------------------------------------------------

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "Wi-Fi started");
        esp_wifi_connect();
    }

    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI(TAG, "Disconnected. Reconnecting...");
        esp_wifi_connect();
    }

    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = static_cast<ip_event_got_ip_t *>(event_data);
        ESP_LOGI( TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
    }
}



// --------------------------------------------------
// ESP-IDF entry point
// --------------------------------------------------

extern "C" void app_main(void)
{
    // --------------------------------------------------
    // NVS
    // --------------------------------------------------

    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }


    // --------------------------------------------------
    // TCP/IP stack
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_netif_init());


    // --------------------------------------------------
    // Event loop
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_event_loop_create_default());


    // --------------------------------------------------
    // Wi-Fi interface
    // --------------------------------------------------

    esp_netif_create_default_wifi_sta();


    // --------------------------------------------------
    // Wi-Fi initialization
    // --------------------------------------------------

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));


    // --------------------------------------------------
    // Wi-Fi event handlers
    // --------------------------------------------------

    ESP_ERROR_CHECK(
        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler,NULL)
    );

    ESP_ERROR_CHECK(
        esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL)
    );


    // --------------------------------------------------
    // Wi-Fi configuration
    // --------------------------------------------------

    wifi_config_t wifi_config = {};
    strcpy((char *)wifi_config.sta.ssid, "#######");
    strcpy((char *)wifi_config.sta.password, "########");


    ESP_ERROR_CHECK(
        esp_wifi_set_mode(WIFI_MODE_STA)
    );

    ESP_ERROR_CHECK(
        esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
    );


    // --------------------------------------------------
    // Start Wi-Fi
    // --------------------------------------------------

    ESP_ERROR_CHECK(
        esp_wifi_start()
    );

    ESP_LOGI(TAG, "Wi-Fi initialization complete");


    TCPShell shell(beacon, battery);
    shell.start();


    // --------------------------------------------------
    // Keep app_main task alive
    // --------------------------------------------------

    while (1)
    {
        vTaskDelay(
            pdMS_TO_TICKS(1000)
        );
    }
}