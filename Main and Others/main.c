#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "initialization.c"
//#include "UART_Handler.h"
#include "Timer_Interrupt_Handler.c"
#include "PIN_Change_Interrupt_Handler.c"
#include "Layer3.c"
#include "Buffer.c"
#include "Miscellaneous.c"


int main(){
    /*!< Initialization */
    port_initialization();
    uart_initialization();
    pin_change_interrupt_initialization();
    timer_initialization();
    sei();/*!< Global interrupt */



    transmit_packet_pointer=&transmit_packet;
    receive_packet_pointer=&receive_packet;
    my_own_packet_pointer=&my_own_packet;
    my_own_packet_pointer->source=0x3;
    my_own_packet_pointer->destination=0x4;
    uint8_t payload_data[6]={my_own_packet_pointer->destination,my_own_packet_pointer->source,0x74,0x65,0x73,0x74}; /*!< Fill with payload data */

    /*!< Fill buffer with predefined data */
    my_own_packet_pointer->preamble=predefined_preamble;
    my_own_packet_pointer->payload[0]=payload_data[0];
    my_own_packet_pointer->payload[1]=payload_data[1];
    my_own_packet_pointer->payload[2]=payload_data[2];
    my_own_packet_pointer->payload[3]=payload_data[3];
    my_own_packet_pointer->payload[4]=payload_data[4];
    my_own_packet_pointer->payload[5]=payload_data[5];
    my_own_packet_pointer->payload_siz= 0x6;
    my_own_packet_pointer->crc=CRC_Computation(my_own_packet_pointer->payload,my_own_packet_pointer->payload_siz);
    receiver_flag=receive_preamble;

    while(1){


        while((priority_type==priority_for_relay)||(priority_type==priority_for_sending_order)||(priority_type==priority_high));
        showLog("------------------------------Rafiqul Islam-----------------------");
        priority_type=priority_for_sending_order;
        *transmit_packet_pointer= *my_own_packet_pointer;
        sender_flag=transmit_preamble;
        //_delay_ms(100);



    }

    return 0;
}

