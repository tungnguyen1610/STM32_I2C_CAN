/*
 * CanCommunication.h
 *
 *  Created on: Mar 11, 2025
 *      Author: KovacsV
 */

#ifndef APP_CANCOMMUNICATION_H_
#define APP_CANCOMMUNICATION_H_

#define CANCOMMUNICATION_UPDATE_MS (3)

typedef struct{
	uint16_t Id;
	uint32_t Message;

}AppCanMessage_t;

uint8_t CanCommunication_Init(uint8_t deviceId);
uint8_t CanCommunication_Send(AppCanMessage_t* pMessage);
uint8_t CanCommunication_Receive(uint8_t fifoNum,AppCanMessage_t* pMessage);
uint8_t CanCommunication_Loop();

#endif /* APP_CANCOMMUNICATION_H_ */
