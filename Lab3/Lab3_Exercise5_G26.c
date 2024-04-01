// Include header files
#include <avr/io.h>
#include <avr/interrupt.h>


void delay_timer0(){
    TCNT0 = 6; // Set initial count to 6

    TCCR0A = 0x00; // Normal mode
    TCCR0B = 0x04; // Prescaler 1:256

}

int main(void){
    DDRB |= 0xFF; // Set PB as outputs

    TIMSK0 |= (1<<TOIE0); // Enable interrupt for timer0

    sei(); // Enable global interrupt

    delay_timer0();  // ISR will be called when overflow happen

    while (1)
    {
        
    }

    return 0;
   
}

ISR(TIMER0_OVF_vect){
    // A counter variable is used to increase the delay because maximum delay for timer0 is 16.384 micro seconds
    static int interrupt_Counter = 0;
    interrupt_Counter++;

    if(interrupt_Counter==25){
        PORTB = PORTB^(1<<5);
        interrupt_Counter = 0;
    }

    TCNT0 = 6; // To maintain same delay timer/counter value again set to initial value which is calculated

}