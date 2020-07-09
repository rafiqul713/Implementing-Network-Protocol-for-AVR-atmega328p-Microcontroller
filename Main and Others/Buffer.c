#pragma once

#include<string.h>
#include<stdlib.h>
struct Packet{
    uint8_t destination; /*!< Store destination address */
    uint8_t source;      /*!< Store source address */
    uint8_t preamble;    /*!< Store preamble */
    uint32_t crc;        /*!< Store CRC */
    uint8_t payload_siz; /*!< Store payload size */
    uint8_t payload[250]; /*!< Store payload */

};

struct Packet transmit_packet,*transmit_packet_pointer; /*!< Transmit buffer */
struct Packet receive_packet,*receive_packet_pointer;   /*!< Receive buffer */
struct Packet my_own_packet,*my_own_packet_pointer;     /*!< My buffer */
uint8_t predefined_preamble=0b01111110;

