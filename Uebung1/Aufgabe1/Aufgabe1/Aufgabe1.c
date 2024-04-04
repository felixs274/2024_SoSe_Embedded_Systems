/*
 * Aufgabe1.c
 *
 * Created: 04.04.2024 17:15:27
 *  Author: scf32306
 */ 


#define F_CPU 16UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	//DDRB = 0x07; // Set first 3 Pins of Port B as outputs
	
	DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2);

    while(1)
    {	
		
		for(short counter = 0x00; counter <= 0x07; counter++){

			PORTB = (0xFF ^ counter)^0xFF;
			
			//_delay_ms(1000);   
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