// Include header files
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    DDRD |= (1<<6); // Set PD6(OC0A) as an output
    TCNT0 = 0x00;   //Initialize the counter
    
    TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01); // Configure Fast PWM mode with non-inverting mode

    TCCR0B |=  (1<<CS00) | (0<<CS01); // Configure the prescaler to 64

    OCR0A = 0x00;   //Configure the PWM pin
    
    while (1)
    // Fading the LED from off to on and on to off
    {
         for(int i = 0;i < 255;i++)
        {
            OCR0A = i;
            _delay_ms(10);
        }
        for(int i = 255;i>0;i--)
        {
            OCR0A = i;
            _delay_ms(10);
        }
        
    }
     
    return 0;
    
}