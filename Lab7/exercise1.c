// Lab 07 - EEPROM / LCD / Keypad
// Group 26
// E/19/424 - Weerasinghe H.A.S.N.
// E/19/426 - Weerasinghe P.M.
// E/19/431 - Wickramaarachchi I.W.A.P.D.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/eeprom.h>  /* Include AVR EEPROM header file */

// ========================== USART ========================== //

// Function to initialize serial communication
void usart_init(){

    // Enable recieve and transmit
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);

    // No paity (UPM00 and UPM02 is set to zero in UCSR0C)
    // Set 8 bit character size (UCSZ00 = 1, UCSZ01 = 1, UCSZ02 = 0) in UCSR0C
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);

    // Selecting asynchronus mode
    UCSR0C &= ~(1<<UMSEL00);

    // Setting the Baudrate (9600) ; X =103
    UBRR0 = 103;

}


// Function to transfer data through serial communication
void usart_send(char character){

    // Monitor the UDRE0 and if it is zero right character to UDRE0 register
    while((UCSR0A&(1<<UDRE0))==0){
    }
    // Send data to the buffer
    UDR0 = character;
}


// Function to recieve data from serial communication
char usart_recieve(){
    // Monitor if RXC0 bit for low (waiting)
    while((UCSR0A&(1<<RXC0))==0){ 
    }
    
    // return the character
    return UDR0;
}




// ========================== EEPROM ========================== //

// Function to write EEPROM
void EEPROMwrite(unsigned int address, char data){

    // Wait for completion of previous write
    while(EECR & (1<<EEPE));

    //set up address and data regs
    EEAR = address;
    EEDR = data;

    // Write logical 1 to EEMPE
    EECR |= (1<<EEMPE);

    // Start EEPROM write
    EECR |= (1<<EEPE);
}


// Function to read from EEPROM
char EEPROMread(unsigned int address){

    // Wait for completion of previous write
    while(EECR & (1<<EEPE));

    //set up address and data regs
    EEAR = address;
    
    // Start EEPROM read
    EECR |= (1<<EERE);

    // Return data
    return EEDR;
}





// Main Function
int main(void){

    // Read sentence from Serial port write it to the EEPROM
    // Initializing Serial communication
    usart_init();

    while(1){

      // Variable for storing the sentence
      char word[1024];

      // Get the first letter
      char letter = usart_recieve();

      // Index
      int i = 0;

      // Receiving from serial communication
      while (letter != '\n') {
        word[i] = letter;
        letter = usart_recieve();
        i++;
      }

      // Add a new character
      word[i] = '\n';

      //Write it to the EEPROM
      for(int j=0; j<i; j++){
          EEPROMwrite(j, word[j]);
      }

      //Variable for get the word from EEPROM
      char receivedWord[1024];

      // read from the EEPROM
      for(int j=0; j<i; j++){
          receivedWord[j] = EEPROMread(j);
          usart_send(EEPROMread(j));
      }

      // Send a new line
      usart_send('\n');
    }

    return 0;
}