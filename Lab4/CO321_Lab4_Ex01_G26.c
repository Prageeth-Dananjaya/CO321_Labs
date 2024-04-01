 // Include the header files
#include <avr/io.h>


int main (void)
{
    DDRD |= (1<<6); // Set PD6(OC0A) as an output 
    TCNT0 = 0x00;   //Initialize the counter
    
    TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01) ; // Configure Fast PWM mode with non-inverting mode

    /*
    Frequency of generated waveform = Frequency of the oscillator / (Prescaler * 256)
    976.56 = 16MHz / (N * 256)
    N = 64    
    */
    TCCR0B |=  (1<<CS00) | (1<<CS01); // Configure the prescaler to 64

    /*
    Duty cycle = ((OCR0A+1)/(256))*100
    50 = ((OCR0A+1)/(256))*100
    OCR0A = 127
    */

    OCR0A = 127;   //Configure the PWM pin
    

   while(1){

   } 
    
  return 0;
    
}