/*
 * Aufgabe1.c
 *
 * Created: 04.04.2024 17:15:27
 *  Author: scf32306
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	char buttonStates = 0;	//0: Reset, 1: Start
	char switchStates = 0;	//0: 2^0, 1: 2^1, 2: 2^2
	char timerEnabled = 0;
	char mask = 0b00000111; // Create mask for the first 3 bits
	char maxCounter = 0;
	char counter = maxCounter;
	DDRD |= (1 << DDD2) | (1 << DDD1) | (1 << DDD0);
	PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4);

	while(1) {
		
		if (counter <= 0) counter = maxCounter;
		if(timerEnabled) counter--;
		PORTD = (PORTD & ~mask) | ~((counter - 1) / 10);
		_delay_ms(100);
		
		// Reset Counter and Stop
		if (PINC & (1 << PINC0)) buttonStates |= 1 << 0;
		else if (buttonStates & (1 << 0)) {
			if (PINC & (1 << PINC2)) switchStates |= 1 << 0;
			else switchStates &= ~(1 << 0);
			if (PINC & (1 << PINC3)) switchStates |= 1 << 1;
			else switchStates &= ~(1 << 1);
			if (PINC & (1 << PINC4)) switchStates |= 1 << 2;
			else switchStates &= ~(1 << 2);
			maxCounter = (switchStates*10)+10;
			buttonStates &= ~(1 << 0);
			counter = maxCounter;
			timerEnabled = 0;
		}
		// Start Counter
		if (PINC & (1 << PINC1)) buttonStates |= 1 << 1;
		else if (buttonStates & (1 << 1)) {
			buttonStates &= ~(1 << 1);
			timerEnabled = 1;
		}
	}
}