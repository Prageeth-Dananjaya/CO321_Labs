// Include header files
#include <avr/io.h>
#include <avr/interrupt.h>


void delay_timer0(){
    TCNT0 = 131; // Set initial count to 131

    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x04; // Prescaler 1:256

}

void delay_timer1(){
    TCNT1 = 34286; // Set initial count to 34286

    TCCR1A = 0x00; // Normal mode
    TCCR1B = 0x04; // Prescaler 1:256

}

int main(void){
    DDRB |= 0xFF; // Set PB5 as an output

    TIMSK0 |= (1<<TOIE0); // Enable interrupt for timer0
    TIMSK1 |= (1<<TOIE1); // Enable interrupt for timer1

    sei(); // Enable global interrupt

    // Two ISRs will be called when overflow happen
    delay_timer0(); 
    delay_timer1();

    while (1)
    {
        
    }

    return 0;   
}

ISR(TIMER0_OVF_vect){
    // Counter variable is used to increase the delay
    static int interrupt_Counter_0 = 0;
    interrupt_Counter_0++;

    if(interrupt_Counter_0==25){
        PORTB = PORTB^(1<<5); // Toggle the LED connected to PIN5 of PORTB
        interrupt_Counter_0 = 0;
    }

    TCNT0 = 6;
}

ISR(TIMER1_OVF_vect){
    
    PORTB = PORTB^(1<<4); // Toggle the LED connected to PIN4 of PORTB
      
    TCNT1 = 34286;

}