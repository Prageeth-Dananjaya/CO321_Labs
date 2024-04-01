// Include header files
#include <avr/io.h>

void delay_timer0(){
    TCNT0 = 131; // Initial count calculated is 131
    
    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x04; // Prescaler used = 1:256

    while ((TIFR0 & 0x01)==0); // Run while overflow happen (TOV0 bit equal to zero)

    // Reset the timer/counter
    TCCR0A = 0x00;
    TCCR0B = 0x00;

    TIFR0 = 0x01; // Reset the flag bit of timer/counter interrupt flag register 

}

int main(void){

    DDRB = DDRB|(1<<5); // Set PB5 as an output

    while (1)
    {
        PORTB = PORTB^(1<<5); // Toggle the LED connected to Pin5 of PORTB
        // Since toggling cannot be seen because delay is too small(2 ms) for loop is used
        for(int i=0; i<500; i++){
            delay_timer0();
        }
        
    }

    return 0;
}