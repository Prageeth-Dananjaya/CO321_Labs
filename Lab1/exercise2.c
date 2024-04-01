// Include header files
#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY 150 // Defining the delay needed in milliseconds

int main(void){

	DDRB = 0xFF;		// Decalared all the pins of PORTB as outputs since some of the pins not working properly in our arduino

	while(1){

		for(int i=0; i<4; i++){
			PORTB = PORTB | (1<<i);		// Set pin i to high
			_delay_ms(BLINK_DELAY);		// Delay of BLINK_DELAY
			PORTB = PORTB & ~(1<<i);	// Set pin i to low
		}

		// Reverse Pattern

		for(int j=2; j>=1; j--){
			PORTB = PORTB |(1<<j);		// Set pin j to High
			_delay_ms(BLINK_DELAY);		// Delay of BLINK_DELAY
			PORTB = PORTB & ~(1<<j);	// Set pin j to low
		}
	}

	return 0;

}