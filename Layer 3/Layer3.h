#pragma once

#define my_own_id                         1
#define broadcasting_id                   0

#define priority_normal                  21
#define priority_for_relay               22
#define priority_for_sending_order       23
#define priority_high                    24

#define return_my_own_msg               101
#define my_own_braodcasting_msg         102
#define broadcasting_msg                103
#define msg_send_to_me                  104
#define msg_send_to_other_node          105
#define unknown                        -111


#define transmit_preamble               31
#define transmit_destination_address    32
#define transmit_source_address         33
#define transmit_crc                    34
#define transmit_payload_size           35
#define transmit_payload                36
#define transmitted                     37



#define receive_preamble                41
#define receive_destination_address     42
#define receive_source_address          43
#define receive_crc                     44
#define receive_payload_size            45
#define receive_payload                 46
#define received_crc_check              47

int priority_type;



/**
 *  \brief This function is used to delete packet
 *  @param f structure pointer, it's type is Packet
 *  @return void nothing has to return from this function
 */
void discard_packet(struct Packet *packet);


/**
 *  \brief This function is used to detect the type of message
 *  @param f structure pointer, it's type is Packet
 *  @return integer type data, which is defined in macro
 */
int type_of_msg(struct Packet *packet);
