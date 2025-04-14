/*
 * Log.c
 *
 *  Created on: Mar 11, 2025
 *      Author: KovacsV
 */


#include "main.h"
#include "Log.h"
#include <string.h>

extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;

// Select which UART to use:
#define LOG_UART_HANDLE (huart1)

#define SENDBUFFER_SIZE 100

uint8_t _enabled=0;
char _sendBuffer[SENDBUFFER_SIZE];

// Sending in progress, mostly used with DMA mode
uint8_t _sending=0;

// Call to notify if transaction has finished
// huart: which UART has finished a transaction
void Log_NotifySendFinished(UART_HandleTypeDef *huart){
	if (&LOG_UART_HANDLE!=huart) return;
	_sending=0;
}

// Init Log module, call once in main
// enabled: true: enable logging
void Log_Init(uint8_t enabled){
	_enabled=enabled;
}

// Returns true if sending is in progress
uint8_t Log_IsSending(){
	return _sending;
}

// Send a log string over UART
// str: string to be sent
void Log(const char* str){
	if (!_enabled){return;}


	// Normál:
	while(1){
		if (LOG_UART_HANDLE.gState==HAL_UART_STATE_READY){break;}
		if (LOG_UART_HANDLE.gState==HAL_UART_STATE_BUSY_RX){break;}
	}

	strncpy(_sendBuffer,str,sizeof(_sendBuffer));
	_sending=1;

	// Indítsa el a küldést HAL_UART_Transmit_IT() függvénnyel!

	HAL_UART_Transmit_IT(&LOG_UART_HANDLE, (uint8_t*)_sendBuffer, strlen(_sendBuffer));
	//DMA esetén:
	//HAL_UART_Transmit_DMA(&LOG_UART_HANDLE, (uint8_t*)_sendBuffer, strlen(_sendBuffer));
}

// Enable logging
void Log_Enable(){
	_enabled=1;
}

// Disable logging
void Log_Disable(){
	_enabled=0;
}
