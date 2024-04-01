// Lab 05 -ADC
// Group 26
// E/19/424 - Weerasinghe H.A.S.N.
// E/19/426 - Weerasinghe P.M.
// E/19/431 - Wickramaarachchi I.W.A.P.D.

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void){

    // Make ADC1 as the input pin
    DDRC = 0;

    // Make PD2 as a output
    DDRD |= (1<<2);

    // Enabling ADC
    ADCSRA |= (1<<ADEN);

    // Use LEFT justification
    ADMUX |= (1<<ADLAR);

    // Select the conversion speed
    // Hence Oscillator is 16MHz and ADC requires less than 200KHz clock we select F/128
    ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2));

    // Select voltage reference channel (use AVCC as reference voltage)
    ADMUX |= (1<<REFS0);

    // Select ADC input channel (ADC1)
    ADMUX |= (1<<MUX0);

    while(1){
        // Activate the start conversion bit
        ADCSRA |= (1<<ADSC);

        // Waiting for conversion to complete
        while(ADCSRA&(1<<ADIF)==0){

        }
        
        // Assuming light is ON at 3.3 V voltage across the LDR

        // Using values of ldr to check whether dark or not
        if(ADCH < 0b10101110){
            PORTD = (1<<2);    // If dark, ON the light
        }
        else{
            PORTD = 0x00;   // If not dark, OFF the light
        }

        // Reset the ADIF
        ADCSRA |= (1<<ADIF);
    }


    return 0;
}