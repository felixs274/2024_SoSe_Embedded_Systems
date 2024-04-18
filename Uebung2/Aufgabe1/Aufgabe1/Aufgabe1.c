/*
* Aufgabe1.c
*
* Created: 11.04.2024 20:15:27
*  Author: daniel
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

uint8_t buttonStates = 0;	//0: Reset, (1: Start (inactive))
uint8_t timerEnabled = 0;
ISR(INT0_vect) { timerEnabled = 1; }

ISR(PCINT1_vect) { buttonStates |= 1 << 0; }

int main(void) {

	uint8_t switchStates = 0;	//0: 2^0, 1: 2^1, 2: 2^2
	uint8_t mask = 0b00000111; // Create mask for the first 3 bits
	uint8_t maxCounter = 0;
	uint8_t counter = maxCounter;
	DDRC |= (1 << DDC2) | (1 << DDC1) | (1 << DDC0);										// LED Outputs
	PORTC |= (1 << PORTC3);																	// Reset Button Pull-up
	PORTD |= (1 << PORTD2) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);					// Start Button / Switches Pull-ups
	
	//INT0 setup
	EICRA &= ~((1<<ISC01)|(1<<ISC00));
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);
	
	//PCINT1 setup
	PCICR &= ~((1<<PCIE2)|(1<<PCIE1)|(1<<PCIE2));
	PCICR |= (1<<PCIE1);
	PCMSK1 |= (1<<PCINT11);
	
	sei();
	
	while(1) {
		
		if (counter <= 0) counter = maxCounter;
		if(timerEnabled) counter--;
		PORTC = (PORTC & ~mask) | ~((counter - 1) / 10);
		_delay_ms(100);
		
		// Reset Counter and Stop
		if (buttonStates & (1 << 0)) {
			if (PIND & (1 << PIND5)) switchStates |= 1 << 0;
			else switchStates &= ~(1 << 0);
			if (PIND & (1 << PIND6)) switchStates |= 1 << 1;
			else switchStates &= ~(1 << 1);
			if (PIND & (1 << PIND7)) switchStates |= 1 << 2;
			else switchStates &= ~(1 << 2);
			maxCounter = (switchStates*10)+10;
			buttonStates &= ~(1 << 0);
			counter = maxCounter;
			timerEnabled = 0;
		}
	}
}
