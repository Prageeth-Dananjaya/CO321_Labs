// Include header files
#include <avr/io.h>
#include <util/delay.h>

#define DELAY 1000 // Define the delay time
int main (void)
{
    DDRD |= (1<<6); // Set PD6(OC0A) as an output
    TCNT0 = 0x00;   //Initialize the counter
    
    TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01); // Configure Fast PWM mode with non-inverting mode

    TCCR0B =  0b00000000; // No clock source

    
    OCR0A = 0xAA;   //Configure the PWM pin
    
    while (1)
    {
        TCCR0B =  0b00000001; // No prescaler
        _delay_ms(1000);
        // Prescaler are change from 1:1024  to 1:8
        for(int i=5; i>=2; i--){
            TCCR0B = i; 
            _delay_ms(DELAY);
        }   
    }
        
    return 0;
    
}