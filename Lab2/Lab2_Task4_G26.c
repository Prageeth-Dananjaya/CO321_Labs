// Include the header files needed
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Debounce delay
#define DEBOUNCE_DELAY_MS 20

volatile uint8_t binaryNumber = 0;

int main() {
    DDRD &= ~((1 << PD2) | (1 << PD3)); // Set PD2 and PD3 as inputs
    DDRB = 0xFF; // Set pins of PORTB as outputs

    EICRA |= (1 << ISC01); // Set for rising edge detection
    EICRA |= (1 << ISC00); // Set for rising edge detection

    EICRA |= (1 << ISC11); // Set for rising edge detection
    EICRA |= (1 << ISC10); // Set for rising edge detection

    sei(); // Enable the global interrupts

    EIMSK |= (1 << INT0) | (1 << INT1); // Enable external interrupts INT0 and INT1

    while (1) {

        PORTB = binaryNumber; // Assigning the binary number the PORTB

    }

    return 0;
}

ISR(INT0_vect) {
    _delay_ms(DEBOUNCE_DELAY_MS); // Debounce delay
    if (!(PIND & (1 << PD2))) {  // Check if button is still pressed
        /*
        ex:
        10111110
        11111110
        --------
        10111110
        */
        binaryNumber = (binaryNumber << 1) & 0xFE;
    }
}

ISR(INT1_vect) {
    _delay_ms(DEBOUNCE_DELAY_MS); // Debounce delay
    if (!(PIND & (1 << PD3))) {  // Check if button is still pressed
        binaryNumber = (binaryNumber << 1) | 0x01;
    }
}
