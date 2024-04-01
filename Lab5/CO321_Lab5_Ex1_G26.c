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

    // Make PORT D as a output
    DDRD |= 0b11111111;

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
        
        _delay_ms(10);
        // Read the values from ADHC and ADCL
        int lower = (int)ADCL;
        int higher = (int)ADCH*256;

        // Get the final value
        int value = lower + higher;

        // Set reading into scale of 8 LEDs as binary number
        PORTD = (int)((value/1024)*5);
    }


    return 0;
}