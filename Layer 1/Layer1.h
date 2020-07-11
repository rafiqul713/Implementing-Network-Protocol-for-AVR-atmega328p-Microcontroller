#pragma once
//#include<avr/delay.h>
/**
 *  This functions is used for debugging purpose LED blinks based on clock signal
 *  \return void nothing has to return from this function
 */
void LED_blink_for_clock_signal_receive();


/**
 *  \brief This functions is used for debugging purpose LED blinks based on data signal
 *  @return void nothing has to return from this function
 */
void LED_blink_for_data_signal_receive();

/**
 *  \brief Change clock signal: from high(1) to low(0), low(0) to high(1)
 *  @return void nothing has to return from this function
 */
void clock_signal_change();


/**
 *  \brief Receive the clock signal when the clock signal is changed, then a new bit
 	\brief is available in the data pin for reading
 *  @return void nothing has to return from this function
 */
void clock_signal_receive();

