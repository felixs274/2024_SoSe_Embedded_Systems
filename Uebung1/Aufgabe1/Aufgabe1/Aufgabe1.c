/*
 * Aufgabe1.c
 *
 * Created: 04.04.2024 17:15:27
 *  Author: scf32306
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2); // Set first 3 bits of PORTB as outputs
	
	while(1)
	{
		
		for(short counter = 0; counter <= 7; counter++){

			PORTB = (PORTB & ~(0b00000111)) | counter;
			
			_delay_ms(1000);
		}
		
	}
}






/*
		 while(counter >= 0){
		   
			
			short mask = 0xFF << counter;
		
			PORTB = mask;
			
			counter--;
			
		
			_delay_ms(300);   
		}

*/