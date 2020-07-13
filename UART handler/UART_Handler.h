#pragma once /*!< allows to include header file when needed otherwise ignore*/
#define BAUD 19200UL
#define BAUDRATE (F_CPU/(16*BAUD)-1)
#include <util/setbaud.h>

/**
 *  \brief UART transmission message: to display message
 *  @param character Unsigned integer to display
 *  @return void nothing has to be returned
 */
void uart_transmission(unsigned char character);



/**
 *  \brief UART receive message: receive message
 *  @return unsigned character, which is received from UART transmission
 */
unsigned char uart_receive();


