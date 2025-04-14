/*
 * SevenSegment.c
 *
 *  Created on: Feb 27, 2025
 *      Author: KovacsV
 */

#include "main.h"
#include "SevenSegment.h"

static uint32_t _lastUpdateMs=0;
uint8_t _selectedDigit=0;
uint8_t _displayBytes[4];


extern SPI_HandleTypeDef hspi3;

const uint8_t chars[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b01110111, // A
    0b01111100, // B
    0b00111001, // C
    0b01011110, // D
    0b01111001, // E
    0b01110001  // F
};

// Initialize 7 segment display module, to be called from main once
void SevenSegment_Init(){
	_displayBytes[0]=0b01000000;
	_displayBytes[1]=0b01000000;
	_displayBytes[2]=0b01000000;
	_displayBytes[3]=0b01000000;
}

void SevenSegment_UpdateLEDs(uint8_t data){

	HAL_GPIO_WritePin(_7SEG__OE_GPIO_Port, _7SEG__OE_Pin, SET);
	HAL_GPIO_WritePin(_7SEL0_GPIO_Port, _7SEL0_Pin, (_selectedDigit&1)!=0);
	HAL_GPIO_WritePin(_7SEL1_GPIO_Port, _7SEL1_Pin, (_selectedDigit&2)!=0);

	HAL_SPI_Transmit(&hspi3, &data, 1, 1);

	HAL_GPIO_WritePin(_7SEG_LE_GPIO_Port, _7SEG_LE_Pin, SET);
	HAL_GPIO_WritePin(_7SEG_LE_GPIO_Port, _7SEG_LE_Pin, RESET);

	HAL_GPIO_WritePin(_7SEG__OE_GPIO_Port, _7SEG__OE_Pin, RESET);
}

// Periodic update for 7 segment display module, to be called periodically from main
void SevenSegment_Loop(){
	uint32_t time=HAL_GetTick();
	if (time-_lastUpdateMs<SEVENSEGMENT_DIGIT_PERIOD_MS){return;}
	_lastUpdateMs=time;

	_selectedDigit&=3;
	uint8_t data=_displayBytes[_selectedDigit&3];

	SevenSegment_UpdateLEDs(data);

	_selectedDigit++;

}

// Update the displayed value as hexadecimal
void SevenSegment_UpdateValueHex(uint16_t value){
	_displayBytes[0]=chars[(value>>12)&0xf];
	_displayBytes[1]=chars[(value>>8)&0xf];
	_displayBytes[2]=chars[(value>>4)&0xf];
	_displayBytes[3]=chars[(value)&0xf];
}

// Update the displayed value as decimal
void SevenSegment_UpdateValueDec(uint16_t value){
	int digit;
	digit=value/1000;
	_displayBytes[0]=chars[digit&0xf];
	value-=digit*1000;
	digit=value/100;
	_displayBytes[1]=chars[digit&0xf];
	value-=digit*100;
	digit=value/10;
	_displayBytes[2]=chars[digit&0xf];
	digit=value%10;
	_displayBytes[3]=chars[digit&0xf];
}
