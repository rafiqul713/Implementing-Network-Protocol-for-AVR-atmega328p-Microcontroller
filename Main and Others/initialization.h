#pragma once


/**
 *  \brief AVR port and pin initialization for input and output purpose
 *  @return void nothing has to return from this function
 */
void port_initialization();


/**
 *  \brief UART initialization for serial communication
 *  @return void nothing has to return from this function
*/
void uart_initialization();


/**
 *  \brief Timer register initialization for Timer Interrupt
 *  @return void nothing has to return from this function
 */
void timer_interrupt_initialization();


/**
 *  \brief PIN change interrupt initialization
 *  @return void nothing has to return from this function
 */
void pin_change_interrupt_initialization();
