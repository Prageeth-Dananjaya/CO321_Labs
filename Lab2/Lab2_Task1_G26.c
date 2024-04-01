// Include the header files
#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRD &= ~(1 << 7);  // Set PD7 as an input
    DDRB = 0x3F;        // Set PB0 - PB5 as outputs (6 LSBs)

    int counter = 0; // Initializing the counter check number of times pressed the button

    while (1) {
        if (PIND & (1 << 7)) {  // If PD7 (push button) is pressed
            _delay_ms(50);     // Debounce the button (adjust the delay as needed)
            if (PIND & (1 << 7)) {
                counter++;
                PORTB = counter & 0x3F;  // Display counter value on 6 LSBs of PORTB
                while (PIND & (1 << 7)) {
                    // Wait for the button to be released
                }
            }
        }
    }

    return 0;
}


