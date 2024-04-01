// // Including header files
// #include <avr/io.h>
// #include <util/delay.h>

// #define BLINK_DELAY 150 // Defining the blink delay

// int main(void){

// 	DDRB = 0xFF;		// Since some of the pins in our arduino are not working properly declaring all ports of PORTB as outputs
	
// 	while(1){
// 		PORTB = 0xFF;            // Declaring all pins to be HIGH
// 		_delay_ms(BLINK_DELAY);  // Delay according to the milliseconds specified above
// 		PORTB = 0x00;            // Declaring all pins to be LOW
// 		_delay_ms(BLINK_DELAY);  // Delay according to the milliseconds specified above
		
// 	}
// 	return 0;
// }

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define BLINK_DELAY_MS 100
unsigned char z=0;
int main(){
	
    DDRD &= ~(1<<7); //PD7 (AIN1) is input
    DDRB = 0xFF;//PB is output
	PORTB = 0x00;

    // EICRA |= (1<<ISC01); //set for rising edge detection
    // EICRA |= (1<<ISC00); //set for rising edge detection
    // sei (); //enable global interrupts
    // EIMSK |= (1<<INT0); //enable external interrupt for into
	
    
    while (1) {
		
		if (PIND & (1<<7))
		{
    		PORTB = z;
			z+=1;
		}
		
    	
    }
    return 0;
}
