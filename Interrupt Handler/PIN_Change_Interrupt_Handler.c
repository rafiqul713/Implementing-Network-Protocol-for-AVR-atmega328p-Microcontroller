#pragma once
#include<avr/io.h>
#include<avr/interrupt.h>
//#include<avr/delay.h>
#include "Layer1.c"
#include "Layer2.c"
#include "Layer3.c"
#include "Buffer.c"
#include "UART_Handler.c"
#include "Timer_Interrupt_Handler.c"
#include "Buffer.c"
#include "Miscellaneous.c"

int ReceiverIndex=0;
int ReceiveBufferIndex=0;
int receiver_flag=1;
int sender_flag;

void pin_change_interrupt_initialization();




/*!< PIN Change interrupt is used for receiving data*/

ISR(PCINT2_vect) {
    /*!<1. Receive preamble which is 8 bit */
    if(receiver_flag==receive_preamble) {
        if(data_receive()) {
            receive_packet_pointer->preamble=write_8_bit(receive_packet_pointer->preamble,7-ReceiverIndex,1);
            //uart_transmission('1');
        }
        else {
            receive_packet_pointer->preamble=write_8_bit(receive_packet_pointer->preamble,7-ReceiverIndex,0);
            //uart_transmission('0');
        }

        ReceiverIndex++;
        if(ReceiverIndex>=8) {
            showLog("Received Preamble: ");
            show_8_bit_data(receive_packet_pointer->preamble);
            if(compare_preamble(receive_packet_pointer->preamble,predefined_preamble)) {
                showLog("\nCorrect Preamble\n");
                ReceiverIndex=0;
                receiver_flag=receive_crc;

            }
            else {
                //showLog("Wrong preamble\n");
                /*!< Wait until detect the correct preamble */
                receive_packet_pointer->preamble=receive_packet_pointer->preamble<<1;/*!< Receive bit by bit and check */



            }



        }

    }

    /*!<2. Receive CRC which is 32 bit */
    else if(receiver_flag==receive_crc) {
        if(data_receive()) {
            receive_packet_pointer->crc=write_32_bit(receive_packet_pointer->crc,31-ReceiverIndex,1);
        }
        else {
            receive_packet_pointer->crc=write_32_bit(receive_packet_pointer->crc,31-ReceiverIndex,0);
        }

        ReceiverIndex++;
        if(ReceiverIndex>=32) {
            showLog("Received CRC: ");
            show_32_bit_data(receive_packet_pointer->crc);
            receiver_flag=receive_payload_size;
            ReceiverIndex=0;
        }

    }

    /*!<3. Receive payload size which is 8 bit */
    else if(receiver_flag==receive_payload_size) {
        if(data_receive()) {
            receive_packet_pointer->payload_siz=write_8_bit(receive_packet_pointer->payload_siz,7-ReceiverIndex,1);
        }
        else {
            receive_packet_pointer->payload_siz=write_8_bit(receive_packet_pointer->payload_siz,7-ReceiverIndex,0);
        }
        ReceiverIndex++;
        if(ReceiverIndex>=8) {
            showLog("Received Payload size: ");
            show_8_bit_data(receive_packet_pointer->payload_siz);
            receiver_flag=receive_destination_address;
            ReceiverIndex=0;
        }

    }

    /*!<4. Receive destination address which is 8 bit */
    else if(receiver_flag==receive_destination_address) {
        if(data_receive()) {
            receive_packet_pointer->destination=write_8_bit(receive_packet_pointer->destination,7-ReceiverIndex,1);

        }
        else {

            receive_packet_pointer->destination=write_8_bit(receive_packet_pointer->destination,7-ReceiverIndex,0);
        }

        ReceiverIndex++;
        if(ReceiverIndex>=8) {
            receive_packet_pointer->payload[0]=receive_packet_pointer->destination;
            showLog("\nReceived Destination address\n");
            show_8_bit_data(receive_packet_pointer->destination);
            receiver_flag=receive_source_address;
            ReceiverIndex=0;
        }

    }

    /*!<5. Receive source address which is 8 bit */
    else if(receiver_flag==receive_source_address) {
        if(data_receive()) {
            receive_packet_pointer->source=write_8_bit(receive_packet_pointer->source,7-ReceiverIndex,1);
        }
        else {
            receive_packet_pointer->source=write_8_bit(receive_packet_pointer->source,7-ReceiverIndex,0);
        }
        ReceiverIndex++;
        if(ReceiverIndex>=8) {
            receive_packet_pointer->payload[1]=receive_packet_pointer->source;
            showLog("\nReceived source address\n");
            receiver_flag=receive_payload;
            show_8_bit_data(receive_packet_pointer->source);
            ReceiverIndex=0;
            ReceiveBufferIndex=2;
        }

    }

    /*!<6. Receive payload. It's size depends on payload size */
    else if(receiver_flag==receive_payload) {
        if(data_receive()) {
            receive_packet_pointer->payload[ReceiveBufferIndex]=write_8_bit(receive_packet_pointer->payload[ReceiveBufferIndex],(7-(ReceiverIndex%8)),1);
        }
        else {
            receive_packet_pointer->payload[ReceiveBufferIndex]=write_8_bit(receive_packet_pointer->payload[ReceiveBufferIndex],(7-(ReceiverIndex%8)),0);
        }

        ReceiverIndex++;
        if(ReceiverIndex%8==0) {
            ReceiveBufferIndex=ReceiveBufferIndex+1;
        }


        if(ReceiverIndex>=(((receive_packet_pointer->payload_siz)-2)*8)) {
            receiver_flag=received_crc_check;
            ReceiverIndex=0;
            showLog("Received payload: ");
            show_payload(receive_packet_pointer->payload,receive_packet_pointer->payload_siz);

        }

    }

    /*!<7. Check CRC. Compare between received CRC and generated CRC */
    else if(receiver_flag==received_crc_check) {
        uint32_t crc_calculation=CRC_Computation(receive_packet_pointer->payload,receive_packet_pointer->payload_siz);
        showLog("CRC Check: \n");
        /*!< CRC is correct */
        if(compare_crc(crc_calculation,receive_packet_pointer->crc)) {
            showLog("Correct CRC");
            int message_type=type_of_msg(receive_packet_pointer); /*!< Check type of message*/

            /*!<1. When message is sent to me */
            if(message_type==msg_send_to_me) {
                showLog("Message send to me");
                discard_packet(receive_packet_pointer);/*!<Delete message */
                //transmit_packet=my_own_packet;


            }

            /*!<2. When message is sent to other node */
            else if(message_type==msg_send_to_other_node) {
                priority_type=priority_high; /*!< Consider as higher priority */
                if(sender_flag==transmitted){
                    sender_flag=transmit_preamble;
                }
                *transmit_packet_pointer=*receive_packet_pointer; /*!< Received data is put into transmit buffer*/
                showLog("Message send to other");

                priority_type=priority_for_relay; /*!<Priority is set for RELAY */

            }

            /*!<3. When message is broadcasting message */
            else if(message_type==broadcasting_msg) {
                priority_type=priority_high; /*!< Consider as higher priority */
                showLog("Broadcasting Message");

                if(sender_flag==transmitted){
                        sender_flag=transmit_preamble;
                }
                *transmit_packet_pointer=*receive_packet_pointer;
                priority_type=priority_for_relay; /*!<Priority is set for RELAY */


            }

            /*!<4. When my message is returned to me */
            else if(message_type==return_my_own_msg) {
                showLog("Return my own messsage");
                showLog("Discard packet");
                *transmit_packet_pointer= *my_own_packet_pointer;
                discard_packet(receive_packet_pointer);
                sender_flag=transmit_preamble;
                priority_type=priority_for_sending_order;

            }

            /*!<5. When my broadcasting message is returned to me */
            else if(message_type==my_own_braodcasting_msg) {
                showLog("My own broadcasting Messsage");
                showLog("Discard packet");
                *transmit_packet_pointer= *my_own_packet_pointer;
                discard_packet(receive_packet_pointer);
                sender_flag=transmit_preamble;
                priority_type=priority_for_sending_order;

            }
            /*!<6. When Receive message from unknown node */
            else if(message_type==unknown){
                showLog("Unknown Message");
            }

            receiver_flag=receive_preamble; /*!< Start to receive again */
            //discard_packet(receive_packet_pointer);
            showLog("----------Receive Cycle Finish----------");

        }

        /*!< CRC is wrong */
        else {
            showLog("Wrong CRC");
            discard_packet(receive_packet_pointer);
            receiver_flag=receive_preamble;

        }

        ReceiverIndex=0;

    }


}
