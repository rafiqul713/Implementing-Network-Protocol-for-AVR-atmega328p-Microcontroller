#pragma once
#include<avr/io.h>
//#include<avr/delay.h>
#include "Timer_Interrupt_Handler.c"
#include "PIN_Change_Interrupt_Handler.c"
#include "Layer1.h"
#include "Miscellaneous.c"


void LED_blink_for_clock_signal_receive() {
    PORTB^=(1<<PB3); /*!< LED toggle based on clock signal receive*/
}

void LED_blink_for_data_signal_receive() {
    PORTB^=(1<<PB2); /*!< LED toggle based on data signal receive*/
}


void clock_signal_change() {
	
    if(PINB & (1<<PB4)) {
        PORTB&=~(1<<PB4); /*!< if clock signal is HIGH,then make it LOW */
    }
    else {
        PORTB|=(1<<PB4); /*!< if clock signal is LOW,then make it HIGH */
    }

}


void clock_signal_receive() {
    LED_blink_for_clock_signal_receive(); /*!< Used for debugging purpose */
}

