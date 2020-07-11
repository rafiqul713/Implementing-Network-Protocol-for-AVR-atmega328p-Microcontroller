#pragma once /*!< allows to include header file when needed otherwise ignore*/
#include<avr/io.h>
#include<stdio.h>
#include<string.h>
#include "Buffer.c"
#include "Layer2.h"
#include "Miscellaneous.h"



int read_8_bit(uint8_t bits, int pos) {
    pos=(1<<pos); /*!< Left shift based on pos value */
    if(bits&pos) { /*!< Logical & to check bit at particular position*/
        return 1;
    }
    else {
        return 0;
    }
}

int read_32_bit(uint32_t bits, int pos) {
    uint32_t mask;
    mask=((uint32_t)0x00000001) << pos; /*!< Casting and left shift*/
    if(bits&mask) {
        return 1;
    }
    else {
        return 0;
    }
}

uint8_t write_8_bit(uint8_t value,int pos, int value_to_write) {
    uint8_t mask1,mask2;
    mask1=((uint8_t)1)<<pos; /*!< Casting and left shift*/
    mask2=((uint8_t)0)<<pos; /*!< Casting and left shift*/
    if(value_to_write==1) {  /*!< When need to write 1*/
        value=value|mask1;   /*!< Logical OR to set bit at particular position*/
    }
    else {
        value=value|mask2;  /*!< When need to write 0*/
    }

    return value;
}

uint32_t write_32_bit(uint32_t value,int pos, int value_to_write) {
    uint32_t mask1,mask2;
    mask1=((uint32_t)0x00000001) << pos; /*!< Casting and left shift*/
    mask2=((uint32_t)0x00000000) << pos; /*!< Casting and left shift*/
    if(value_to_write==1) {              /*!< When need to write 1*/
        value=value|mask1;               /*!< Logical OR to set bit at particular position*/
    }
    else {
        value=value|mask2;               /*!< When need to write 0*/
    }

    return value;
}

void showLog(char msg[]) {
    int i=0;
    uart_transmission('\r');
    uart_transmission('\n');
    for(i=0; msg[i]!='\0'; i++) { /*!< Display message until getting the null value*/
        uart_transmission(msg[i]);/*!< UART function to display message*/

    }

}

int compare_preamble(uint8_t a, uint8_t b) {
    if(!(a^b)) {                 /*!< Bit compare using XOR*/
        return 1;                /*!< O XOR 1 = 1*/
    }
    else {
        return 0;                /*!< O XOR 0 = 0, 1 XOR 1 = 0*/
    }
}

void show_8_bit_data(uint8_t data) {
    int i;
    uart_transmission('\n');
    uart_transmission('\r');
    for(i=7; i>=0; i--) {       /*!< Read from MSB*/
        if(read_8_bit(data,i)) { /*!< Read data at particular position*/
            uart_transmission('1'); /*!< Display 1*/
        }
        else {
            uart_transmission('0'); /*!< Display 0*/
        }
    }
    uart_transmission('\n');
    uart_transmission('\r');
}

void show_32_bit_data(uint32_t data) {
    int i;
    uart_transmission('\n');
    uart_transmission('\r');
    for(i=31; i>=0; i--) {       /*!< Read from MSB*/
        if(read_32_bit(data,i)) { /*!< Read data at particular position*/
            uart_transmission('1'); /*!< Display 1*/
        }
        else {
            uart_transmission('0'); /*!< Display 0*/
        }
    }
    uart_transmission('\n');
    uart_transmission('\r');
}


void show_payload(uint8_t *data, uint8_t length) {
    int i,j;
    uart_transmission('\n');
    uart_transmission('\r');
    for(i=0; i<length/8; i++) { /*!< Iterate over every element of the array */
        for(j=7; j>=0; j--) { /*!< Read from the MSB*/
            if(read_32_bit(data[i],j)) {
                uart_transmission('1'); /*!< Display 1*/
            }
            else {
                uart_transmission('0'); /*!< Display 0*/
            }
        }
    }
    uart_transmission('\n');
    uart_transmission('\r');
}


int compare_crc(uint32_t a, uint32_t b) {
    if(!(a^b)) {    /*!< Bit compare using XOR*/
        return 1;   /*!< O XOR 1 = 1*/
    }
    else {
        return 0;   /*!< O XOR 0 = 0, 1 XOR 1 = 0*/
    }
}
