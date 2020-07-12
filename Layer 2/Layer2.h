#pragma once


/**
 *  \brief Read the status of the receiver data pin
 *  @return integer data which are 0 or 1
 */
int data_receive();

/**
 *  \brief Transmit data signal as HIGH or 1 through the data pin
 *  @return void nothing has to be returned
 */
void tranmit_1();

/**
 *  \brief Transmit data signal as LOW or 0 through the data pin
 *  @return void nothing has to be returned
 */
void tranmit_0();



