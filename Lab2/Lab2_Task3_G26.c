// Include the header files
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int counter = 0; // Variable to count number of times push button release

// Debounce delay function
void debounce_delay() {
    _delay_ms(10); // Adjust this delay as needed
}

int main() {
    DDRD &= ~(1 << 2); // Set PD2 (INT0) as an input
    DDRB = 0xFF;      // Set PB as an output

    EICRA |= (1 << ISC01); // Set for falling edge detection
    EICRA &= ~(1 << ISC00); // Set for falling edge detection

    sei(); // Enable global interrupts

    EIMSK |= (1 << INT0); // Enable external interrupt for INT0

    while (1) {
        
    }

    return 0;
}

ISR(INT0_vect) {
    debounce_delay(); // Add debounce delay
    if (!(PIND & (1 << PD2))) { // Check if the button is still pressed
        counter++;
        PORTB = counter;
        if (counter == 256) {
            counter = 0;
        }
    }
}
