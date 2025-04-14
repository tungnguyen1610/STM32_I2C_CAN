/*
 * SevenSegment.h
 *
 *  Created on: Feb 27, 2025
 *      Author: KovacsV
 */

#ifndef APP_SEVENSEGMENT_H_
#define APP_SEVENSEGMENT_H_

#define SEVENSEGMENT_DIGIT_PERIOD_MS (1)

// Initialize 7 segment display module, to be called from main once
void SevenSegment_Init();

// Periodic update for 7 segment display module, to be called periodically from main
void SevenSegment_Loop();

// Update the displayed value as hexadecimal
void SevenSegment_UpdateValueHex(uint16_t value);

// Update the displayed value as decimal
void SevenSegment_UpdateValueDec(uint16_t value);

#endif /* APP_SEVENSEGMENT_H_ */
