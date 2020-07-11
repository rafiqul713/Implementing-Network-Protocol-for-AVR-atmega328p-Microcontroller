#pragma once /*!< allows to include header file when needed otherwise ignore*/
#include<avr/io.h>
#include<stdio.h>
#include<string.h>
#include "Buffer.c"
#include "Layer2.h"

/**
 *  \brief Display a single character in the minicom command line interface
 *  @param character Character for display in the minicom command line interface
 *  @return void nothing has to return from this function
 */
void uart_transmission(unsigned char character);


/**
 *  \brief Display message consists of string
 *  @param msg Message for display in the minicom command line interface
 *  @param void nothing has to return from this function
 */
void showLog(char msg[]);


/**
 *  \brief Read from 8 bit unsigned integer
 *  @param bits The 8 bit integer to read to
 *  @param pos  Read bit at particular position
 *  @return int data 1 or 0
 */
int read_8_bit(uint8_t bits,int pos);


/**
 *  \brief Read from 32 bit unsigned integer
 *  @param bits The 32 bit integer to read to
 *  @param pos  Read bit at particular position
 *  @return int data which are 1 or 0
 */
int read_32_bit(uint32_t bits,int pos);


/**
 *  \brief Write in 8 bit unsigned integer
 *  @param  value The 8 bit integer to write to
 *  @param  pos Write at particular position
 *  @param  value_to_write int data which are 0 or 1
 *  @return uint8_t data
 */
uint8_t write_8_bit(uint8_t value,int pos, int value_to_write);


/**
 *  \brief Write in 32 bit unsigned integer
 *  @param  value The 32 bit integer to write to
 *  @param  pos Write at particular position
 *  @param  value_to_write int data which are 0 or 1
 *  @return uint32_t data
 */
 uint32_t write_32_bit(uint32_t value,int pos, int value_to_write);


/**
 *  \brief Compare between received preamble and predefined preamble
 *  @param a 8 bit unsigned integer, which is predefined
 *  @param b 8 bit unsigned integer, which is received
 *  @return int data, which is 1 if match otherwise, 0 if does not match
 */
int compare_preamble(uint8_t a, uint8_t b);


/**
 *  \brief Compare between received CRC and generated CRC from payload
 *  @param a 32 bit unsigned integer, which is generated from the payload
 *  @param b 32 bit unsigned integer, which is received
 *  @return int data, which is 1 if match otherwise, 0 if does not match
 */
int compare_crc(uint32_t a, uint32_t b);

/**
 *  \brief Display payload message
 *  @param data 8 bit unsigned character array
 *  @param length Length of the payload
 *  @return void nothing has to return
 */
void show_payload(uint8_t *data, uint8_t length);

