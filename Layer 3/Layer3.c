#pragma once
#include "Layer3.h"
#include "Miscellaneous.c"

void discard_packet(struct Packet *packet){
	packet->destination=0;
	packet->source=0b00000000;
	packet->preamble=0b00000000;
	packet->payload_siz=0b00000000;
	packet->crc=0b00000000000000000000000000000000;
}


int type_of_msg(struct Packet *packet){
    int message_type=unknown; /*!< At first initiaze message type as unknown */
    int source_address = packet->source; /*!< Extract the source address*/
    int destination_address=packet->destination; /*!< Extract destination address*/

    if((source_address==my_own_id) && (destination_address!=broadcasting_id)){
        message_type=return_my_own_msg; /*!<Return my own message to me */

    }
    else if((source_address==my_own_id) && (destination_address==broadcasting_id)){
        message_type=my_own_braodcasting_msg; /*!<Receive my own broadcasting message*/
    }


    else if((!(source_address==my_own_id)) && (destination_address==broadcasting_id)){
        message_type=broadcasting_msg; /*!< Receive broadcasting message */
    }

    else if((!(source_address==my_own_id)) && (destination_address==my_own_id)){
        message_type=msg_send_to_me; /*!< Message send to me*/
    }
    else if((!(source_address==my_own_id)) && (!(destination_address==my_own_id)) &&
        (!(destination_address==broadcasting_msg))){
        message_type=msg_send_to_other_node; /*!<Message send to other node: relay*/
    }

    else{
        message_type=unknown; /*!<Message from unknown source which can not be identified */
    }

    return message_type;

}
