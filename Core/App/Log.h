/*
 * Log.h
 *
 *  Created on: Mar 11, 2025
 *      Author: KovacsV
 */

#ifndef APP_LOG_H_
#define APP_LOG_H_

// Init Log module, call once in main
// enabled: true: enable logging
void Log_Init(uint8_t enabled);

// Send a log string over UART
// str: string to be sent
void Log(const char* str);

// Enable logging
void Log_Enable();

// Disable logging
void Log_Disable();

// Call to notify if transaction has finished
// huart: which UART has finished a transaction
void Log_NotifySendFinished(UART_HandleTypeDef *huart);

// Returns true if sending is in progress
uint8_t Log_IsSending();


#endif /* APP_LOG_H_ */
