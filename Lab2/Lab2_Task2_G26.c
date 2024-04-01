// include the header files
#include <avr/io.h>
#include <avr/interrupt.h>

int main(){

    DDRD &= ~(1<<2); // Set PD2 (INT0) as an input
    DDRB |= (1<<0); // Set PB0 as an output

    EICRA |= (1<<ISC01); // Set for falling edge detection
    EICRA &= ~(1<<ISC00); // Set for falling edge detection

    sei(); // enable global interrupts

    EIMSK |= (1<<INT0); // enable external interrupt for INT0

    while (1)
    {
       
    }

    return 0;
}

ISR(INT0_vect){
    PORTB = ~ PORTB; // Toggle the PORTB
}