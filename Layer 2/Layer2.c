#pragma once
#include<avr/io.h>
//#include<util/delay.h>
#include<stdio.h>
#include<string.h>
#include "CRC.c"
#include "Buffer.c"
#include "Layer2.h"
#include "Miscellaneous.c"

void tranmit_1() {

    PORTB|=(1<<PB5); /*!< Make PB5 pin HIGH for data transmit */

}

void tranmit_0() {

    PORTB&=~(1<<PB5); /*!< Make PB5 pin LOW for data transmit*/
}



int data_receive() {
    if(PIND&(1<<PD5)) { /*!< Receiver read the status of PD5 pin*/
        return 1;   /*!< When PD5 is HIGH return 1 */
    }
    else {
        return 0; /*!< When PD5 is LOW return 0 */
    }
}
