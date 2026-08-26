#include "TCPShell.hpp"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include <stdlib.h>



static const char *TAG = "SHELL";

// adc_oneshot_unit_handle_t adc_handle;
// adc_cali_handle_t adc_cali_handle;




TCPShell::TCPShell(Beacon& beacon, Battery& battery)
    : server_socket(-1), battery(battery), beacon(beacon)
    
{
    
}

void TCPShell::start(){
    xTaskCreate(task, "tcp_server", 4096, this, 5, NULL);
}

void TCPShell::task(void *arg){
    TCPShell *shell = static_cast<TCPShell *>(arg);
    shell->run();
    vTaskDelete(NULL);
}

void TCPShell::run(){

    // Motor PWM setup
    ledc_timer_config_t motor_timer = {};
    motor_timer.speed_mode = LEDC_LOW_SPEED_MODE;
    motor_timer.timer_num = LEDC_TIMER_0;
    motor_timer.duty_resolution = LEDC_TIMER_10_BIT;
    motor_timer.freq_hz = 5000;
    motor_timer.clk_cfg = LEDC_AUTO_CLK;

    ledc_timer_config(&motor_timer);

    ledc_channel_config_t motor_channel = {};

    motor_channel.speed_mode = LEDC_LOW_SPEED_MODE;
    motor_channel.intr_type = LEDC_INTR_DISABLE;
    motor_channel.timer_sel = LEDC_TIMER_0;
    motor_channel.duty = 0;
    motor_channel.hpoint = 0;

    // Backward
    motor_channel.gpio_num = GPIO_NUM_33;
    motor_channel.channel = LEDC_CHANNEL_0;
    ledc_channel_config(&motor_channel);

    // Forward
    motor_channel.gpio_num = GPIO_NUM_27;
    motor_channel.channel = LEDC_CHANNEL_1;
    ledc_channel_config(&motor_channel);

    // anticlockwise
    motor_channel.gpio_num = GPIO_NUM_32; 
    motor_channel.channel = LEDC_CHANNEL_2;
    ledc_channel_config(&motor_channel);

    // Forward
    motor_channel.gpio_num = GPIO_NUM_25;
    motor_channel.channel = LEDC_CHANNEL_3;
    ledc_channel_config(&motor_channel);

    ESP_LOGI(TAG, "Motor PWM initialized on GPIO25");



    char rx_buffer[128];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (server_socket < 0){
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(5000);

    int err = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (err < 0){
        ESP_LOGE(TAG,"Unable to bind: errno %d",errno);
        close(server_socket);
        return;
    }

    err = listen(server_socket, 1);

    if (err < 0){
        ESP_LOGE(TAG,"Unable to listen: errno %d", errno);
        close(server_socket);
        return;
    }

    ESP_LOGI(TAG,"TCP server listening on port 5000");

    while (true)
    {
        socklen_t addr_len = sizeof(client_addr);

        int client_socket = accept(server_socket,(struct sockaddr *)&client_addr, &addr_len);

        if (client_socket < 0){
            ESP_LOGE(TAG,"accept failed: errno %d", errno);
            continue;
        }

        ESP_LOGI(TAG,"Client connected");

        // Send initial prompt
        const char *prompt = "roth> ";

        send(client_socket, prompt, strlen(prompt), 0);

        while (true) {
            int len = recv(client_socket, rx_buffer,sizeof(rx_buffer) - 1, 0);

            if (len <= 0){
                ESP_LOGI(TAG, "Client disconnected");
                break;
            }

            rx_buffer[len] = '\0';

            // Remove newline
            rx_buffer[strcspn(rx_buffer, "\r\n")] = '\0';

            ESP_LOGI(TAG, "Command: %s", rx_buffer );
            char response[128];

            if (strcmp(rx_buffer, "beacon on") == 0){
                beacon.on();
                strcpy(response, "Done!\n");
                strcat(response, prompt);
            }

            else if (strcmp(rx_buffer, "beacon off") == 0) {
                beacon.off();

                strcpy(response, "Done!\n");
                strcat(response, prompt);
            }

            else if (strcmp(rx_buffer, "vbat") == 0) {

                float voltage = battery.getVoltage();
                float percentage = battery.getPercentage();

                std::string voltage_str = std::to_string(voltage);
                std::string percentage_str = std::to_string(percentage);

                strcpy(response, "VBAT: ");
                strcat(response, voltage_str.c_str());
                strcat(response, "V (");
                strcat(response, percentage_str.c_str());
                strcat(response, "%)\n");
                
            }
            else if (strncmp(rx_buffer, "move ", 5) == 0) {

                int channel = 0;
                int power = 0;
                int start_pulse = 20;
                int duration = 0;

                int args = sscanf(rx_buffer + 5, "%d %d %d %d", &channel, &power, &start_pulse, &duration);

                if (args >= 1) {

                    if (power < 0) power = 0;
                    if (power > 100) power = 100;

                    if (start_pulse < 0) start_pulse = 0;
                    if (start_pulse > 100) start_pulse = 100;

                    uint32_t pulse_duty = (start_pulse * 1023) / 100;
                    uint32_t normal_duty = (power * 1023) / 100;

                    ledc_channel_t ch = LEDC_CHANNEL_0; // Default to backward
                    if (channel == 0) {
                        ch = LEDC_CHANNEL_0;
                    } else if (channel == 1) {
                        ch = LEDC_CHANNEL_1;
                    } else if (channel == 2) {
                        ch = LEDC_CHANNEL_2;
                    }else if (channel == 3) {
                        ch = LEDC_CHANNEL_3;
                    } 
                    else {
                        strcpy(response, "Invalid channel. Use 0 for backward or 1 for forward.\n");
                        strcat(response, prompt);
                        send(client_socket, response, strlen(response), 0);
                        continue;
                    }

                    // Startup pulse
                    ledc_set_duty(
                        LEDC_LOW_SPEED_MODE,
                        ch,
                        pulse_duty
                    );
                    ledc_update_duty(
                        LEDC_LOW_SPEED_MODE,
                        ch
                    );

                    // Hold pulse
                    vTaskDelay(pdMS_TO_TICKS(duration));

                    // Return to requested power
                    ledc_set_duty(
                        LEDC_LOW_SPEED_MODE,
                        ch,
                        normal_duty
                    );
                    ledc_update_duty(
                        LEDC_LOW_SPEED_MODE,
                        ch
                    );

                    snprintf(
                        response,
                        sizeof(response),
                        "Move: ch=%d power=%d%% pulse=%d%% duration=%dms\n",
                        channel,
                        power,
                        start_pulse,
                        duration
                    );

                }
            }

            else {
                strcpy(response, "Joy Jagannath!\n");
                
            }

            // strcat(response, prompt);
            send(client_socket, response, strlen(response),0);
        }

        close(client_socket);
    }
}