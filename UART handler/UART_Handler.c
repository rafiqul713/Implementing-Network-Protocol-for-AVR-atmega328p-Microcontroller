#include <avr/io.h>
#include "UART_Handler.h"
//#include <util/delay.h>


void uart_transmission(unsigned char send_data){
    while(!(UCSR0A & (1<<UDRE0))); /*!< Wait until the register is free */
    UDR0= send_data; /*!<write the new data in Transmit Buffer (UDR)*/
}

unsigned char uart_receive(){
    while(!(UCSR0A & (1<<RXC0))); /*!< Wait until the data is received */
    return UDR0; // UDR return 8 bit
 }
