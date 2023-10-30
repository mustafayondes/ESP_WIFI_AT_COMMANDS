/*
 * wifi.c
 *
 * Created on: Sep 4, 2023
 * Author: Rise-X Teknoloji MUSTAFA
 */

#include "main.h"
#include "wifi.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;

// AT komutları için sabitler
const char diziTransmit[] = "AT\r\n";
const char ESP_MODE_CMD[] = "AT+CWMODE=1\r\n";
const char ESP_Connect[] = "AT+CWJAP=\"Mustafa\",\"1234567mm\"\r\n";
const char ESP_APi[] = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n";
const char ESP_Send[] = "AT+CIPSEND=500\r\n";
const char ESP_SendDataTemplate[] = "GET /update?api_key=%s&field1=%s\r\n";
const char ESP_Send_Close[] = "AT+CIPCLOSE\r\n";

// Veri gönderme için kullanılan buffarlar
char sendBuff[256], sendBuff2[256], sendBuff3[256];
char diziReceive[400];
// Gönderilen veri uzunlukları
uint8_t buffLen, buffLen2;

char ESP_ConnectReceive[150];

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

// Wi-Fi test function
void wifi_test() {
    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)diziTransmit, sizeof(diziTransmit));
    HAL_Delay(1000);
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)diziReceive, sizeof(diziReceive));
}

// Wi-Fi connection function
void wifi_connect() {
    HAL_UART_Transmit(&huart2, (uint8_t *)ESP_MODE_CMD, sizeof(ESP_MODE_CMD), HAL_MAX_DELAY);
    HAL_Delay(1000);
    HAL_UART_Transmit(&huart2, (uint8_t *)ESP_Connect, sizeof(ESP_Connect), HAL_MAX_DELAY);
    HAL_UART_Receive(&huart2, (uint8_t *)diziReceive, sizeof(diziReceive), HAL_MAX_DELAY);
}

//Sending data to thingspeak from esp32 on stm32
void ESP32_SendDataToThingSpeak( char * API_KEY,int  value) {
    // First Connect to server
    buffLen = sprintf(sendBuff,ESP_APi );
    HAL_UART_Transmit(&huart2, (uint8_t *)sendBuff, buffLen, 1000);

    // Preapering data after connection
    buffLen = sprintf(sendBuff3, "GET /update?api_key=%s&field1=%d\r\n", API_KEY, value);
    buffLen2 = sprintf(sendBuff2, "AT+CIPSEND=%d\r\n", 500);

    // Send data to thingspeak
    HAL_UART_Transmit(&huart2, (uint8_t *)sendBuff2, buffLen2, 1000);
    HAL_Delay(1000);
    HAL_UART_Transmit(&huart2, (uint8_t *)sendBuff3, buffLen, 1000);
}






