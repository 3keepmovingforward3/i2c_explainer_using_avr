/*
 * explaining_i2c.c
 *
 * Created: 8/3/2020 11:43:38 AM
 * Author : Benjamin Blouin
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include "SSD1306.h"
#include "i2c.h"

// Binary Output Format Macro
//
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
(byte & 0x80 ? '1' : '0'), \
(byte & 0x40 ? '1' : '0'), \
(byte & 0x20 ? '1' : '0'), \
(byte & 0x10 ? '1' : '0'), \
(byte & 0x08 ? '1' : '0'), \
(byte & 0x04 ? '1' : '0'), \
(byte & 0x02 ? '1' : '0'), \
(byte & 0x01 ? '1' : '0')

// Address
// Assume worker address is 0xDC
//
size_t exampleAddress = 0b11111100;

int main(void)
{
    OLED_init();

	PORTC |= 1<<PINC6; //push button pull-up resistor
	PCMSK2 |= (1<<PCINT22); //push button pin-change interrupt
	PCICR |= (1<<PCIE2); //pin change interrupt
	sei(); //set enable interrupt

	while (1)
    {
	}
}

// Interrupt Service Routine
//
ISR(PCINT2_vect){
	OLED_GoToLine(0);
	OLED_Printf("i2c start called \nadr<<0: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(exampleAddress));
	OLED_Printf("\nadr<<1: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(exampleAddress<<1));
	i2c_start(exampleAddress<<1); //arbitrary address + write enable
}
