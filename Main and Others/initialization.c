#include<avr/io.h>
#include "initialization.h"
#include "UART_Handler.h"
#include<avr/io.h>
#include<avr/interrupt.h>

void port_initialization(){
    /*!< Receive PIN Configuration*/
    DDRD&=~(1<<PD4);/*!< Clock Receive*/
    DDRD&=~(1<<PD5);/*!< Data Receive*/

    /*!< Send PIN configuration*/
    DDRB|=(1<<PB4);/*!< Clock Send*/
    DDRB|=(1<<PB5);/*!< Data Send*/

    /*!< LED output*/
    DDRB|=(1<<PB3);/*!< to indicate clock signal receive*/
    DDRB|=(1<<PB2);/*!< to indicate data signal receive*/
}

void uart_initialization(){
    /*!< Set baud rate
     *   UBRR is a 16 bit register which is used to set the
     *   baud rate of UART
     */
    UBRR0H =  (unsigned char)BAUDRATE>>8;
    UBRR0L =  (unsigned char)BAUDRATE;
    /*!< Transmitter and Receiver is Enabled
     *   TXEN bit 1 Enable Transmission 0 Disable Transmission
     *   RXEN bit 1 Enable Reception 0 Disable Reception
     */
    UCSR0B|= (1<<TXEN0)|(1<<RXEN0);
    /*!< UCSZ0 and UCSZ1 are used to select the number of data bits
     to be transmitter
     */
    UCSR0C|= (1<<USBS0)|(3<<UCSZ00); /*!< Asynchornous mode*/


}


void timer_initialization(){
	TIMSK0 |= (1 << OCIE0A); /*!< Compare match A*/
	TCCR0A |= (1 << WGM01);  /*!< CTC mode*/
	TCCR0B |= (1 << CS02);   /*!< Clock/256 = 46875 (prescalar 256)*///
	OCR0A = 0x2f;
    //OCR0A = 0x600;
}

void pin_change_interrupt_initialization(){
  PCICR|= (1<<PCIE2); /*!< enabled PCINT[23:16] pin will cause an interrupt*/
  PCMSK2|=(1<<PCINT20);/*!< pin change interrupt for PD4 or clock receive signal*/
}


