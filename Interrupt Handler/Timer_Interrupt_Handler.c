#pragma once
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
//#include "UART_Handler.h"
#include "Layer1.c"
#include "Layer2.c"
#include "Layer3.c"
#include "Buffer.c"
#include "Miscellaneous.c"


int TransmitIndex=0;
int sender_flag=2;
int arrayIndex=0;


int Compare_A=0;
int Compare_B=0;

 /*!< Timer interrupt for transmitting data */
ISR(TIMER0_COMPA_vect) {
    Compare_A=Compare_A+1;
    if(Compare_A>100) {
        clock_signal_change();
        _delay_ms(1000);
        Compare_A=0;
        /*!< Check priority type */
        if((priority_type==priority_for_sending_order) ||(priority_type==priority_for_relay)) {
            //_delay_ms(1000);
            /*!< 1. Preamble transmit which is 8 bit data */
            if(sender_flag==transmit_preamble) {
                if(read_8_bit(transmit_packet_pointer->preamble,7-TransmitIndex)) {
                    tranmit_1();
                }

                else if(!read_8_bit(transmit_packet_pointer->preamble,7-TransmitIndex)) {
                    tranmit_0();
                }
                TransmitIndex++;
                if(TransmitIndex>=8) {
                    TransmitIndex=0;
                    showLog("Transmit Preamble: ");
                    show_8_bit_data(transmit_packet_pointer->preamble);
                    sender_flag=transmit_crc;

                }

            }

            /*!<2.CRC transmit which is 32 bit data*/
            else if(sender_flag==transmit_crc) {
                if(read_32_bit(transmit_packet_pointer->crc,31-TransmitIndex)) {
                    tranmit_1();
                }

                else if(!read_32_bit(transmit_packet_pointer->crc,31-TransmitIndex)) {
                    tranmit_0();
                }
                TransmitIndex++;
                if(TransmitIndex>=32) {
                    showLog("Transmit CRC: ");
                    sender_flag=transmit_payload_size;
                    show_32_bit_data(transmit_packet_pointer->crc);
                    TransmitIndex=0;
                }

            }

            /*!<3.Payload size transmit which is 8 bit data*/
            else if(sender_flag==transmit_payload_size) {
                if(read_8_bit(transmit_packet_pointer->payload_siz,7-TransmitIndex)) {
                    tranmit_1();

                }

                else if(!read_8_bit(transmit_packet_pointer->payload_siz,7-TransmitIndex)) {
                    tranmit_0();

                }
                TransmitIndex++;
                if(TransmitIndex>=8) {
                    showLog("Payload size send: ");
                    show_8_bit_data(transmit_packet_pointer->payload_siz);
                    TransmitIndex=0;
                    sender_flag=transmit_destination_address;
                }
            }

            /*!<4.Destination address transmit which is 8 bit data*/
            else if(sender_flag==transmit_destination_address) {
                if(read_8_bit(transmit_packet_pointer->destination,7-TransmitIndex)) {
                    tranmit_1();
                }

                else if(!read_8_bit(transmit_packet_pointer->destination,7-TransmitIndex)) {
                    tranmit_0();
                }
                TransmitIndex++;
                if(TransmitIndex>=8) {
                    showLog("\nDestination address send\n");
                    show_8_bit_data(transmit_packet_pointer->destination);
                    sender_flag=transmit_source_address;
                    TransmitIndex=0;
                }

            }

            /*!<5.Source address transmit which is 8 bit data*/
            else if(sender_flag==transmit_source_address) {
                if(read_8_bit(transmit_packet_pointer->source,7-TransmitIndex)) {
                    tranmit_1();
                }
                else if(!read_8_bit(transmit_packet_pointer->source,7-TransmitIndex)) {
                    tranmit_0();
                }
                TransmitIndex++;
                if(TransmitIndex>=8) {
                    showLog("\nSource address send\n");
                    sender_flag=transmit_payload;
                    show_8_bit_data(transmit_packet_pointer->source);
                    TransmitIndex=0;
                    arrayIndex=2;
                }

            }

            /*!<6.Payload transmit. It's size depends on payload size */
            else if(sender_flag==transmit_payload) {

                if(read_8_bit(transmit_packet_pointer->payload[arrayIndex],(7-(TransmitIndex%8)))) {
                    tranmit_1();
                }

                else if(!read_8_bit(transmit_packet_pointer->payload[arrayIndex],(7-(TransmitIndex%8)))) {
                    tranmit_0();
                }
                TransmitIndex++;
                if(TransmitIndex%8==0) {
                    arrayIndex=arrayIndex+1;

                }

                if(TransmitIndex>=(((transmit_packet_pointer->payload_siz)-2)*8)) {
                    showLog("Send payload: ");
                    show_payload(transmit_packet_pointer->payload,transmit_packet_pointer->payload_siz*8);
                    TransmitIndex=0;
                    if(priority_type==priority_for_sending_order) {
                        showLog("Transmitted....!");

                    }

                    priority_type=priority_normal; /*!<Set sending priority as normal*/
                    discard_packet(transmit_packet_pointer);
                    sender_flag=transmitted;
                    showLog("----------------transmit cycle finish----------------------");

                }


            }

        }

    }

}

