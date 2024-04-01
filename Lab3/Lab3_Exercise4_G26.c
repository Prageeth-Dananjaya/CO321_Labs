// Include header files
#include <avr/io.h>
#include <avr/interrupt.h>


void delay_timer1(){
    TCNT1 = 49911; // Set the initial counter value of timer/counter register

    TCCR1A = 0x00;  // Normal mode 
    TCCR1B = 0x05;  // prescaler 1:1024 

}

int main(void){
    DDRB |= 0xFF; // Set PB as outputs
    DDRC |= 0xFF; // Set PC as outputs
    
    PORTC = 0x01; // PORTC is initialized with 1 to use for shifting

    TIMSK1 |= (1<<TOIE1); // Enable interrupt for timer1

    sei(); // Enable global interrupt

    delay_timer1(); // After overflow happen this function will call the ISR

    while (1)
    {
        
    }
    
    return 0;
}

ISR(TIMER1_OVF_vect){
    PORTB = PORTB^(1<<5); // Toggle pin5 of PORTB
     // Initial value for next call is set to maintain 1 second delay
    static int direction = 1; // This variable is used to guide the shifting direction

    if(PORTC==0b00000001){
        direction=1;
    }
    if(PORTC==0b00001000){
        direction=0;
    }


    if(direction==0){
        PORTC = (PORTC>>1);
    }else{
        PORTC = (PORTC<<1);
    }

    TCNT1 = 49911; // Timer/counter value is set to initial value to maintain same amount of delay

}


