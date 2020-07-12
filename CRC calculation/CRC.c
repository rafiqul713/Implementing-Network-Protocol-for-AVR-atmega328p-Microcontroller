#include<avr/io.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "CRC.h"


uint32_t CRC_Computation(uint8_t *bytes,int len){
    const uint64_t polynomial=0x104C11DB7; /*!< CRC polynomial */
    uint32_t crc = 0;
    int i,byte;
    for(byte=0;byte<len;byte++){
        crc^=((uint32_t)bytes[byte])<<24; /*!< Move byte into MSB */
        for(i=0;i<8;i++){
            if((crc&0x80000000)!=0){ /*!< Check if MSB is 1 or 0 */
                crc=(uint32_t)((crc<<1)^polynomial); /*!< Left shift 1 and do XOR operation */
            }
            else{
                crc <<= 1; /*!< Left shift 1 if MSB is 0 */

            }
        }
    }

    return crc;
}
