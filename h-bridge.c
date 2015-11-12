/****************************************************************

 *            Cool of Engineering Ltd

 *            C212 City Campus, CPIT

 *            (c) CoE, 2015

 *

 *     Filename: DVR.c

 *     Developer:Cameron McDonald

 *     Date:    2/11/2015

 *     Description:

 *            Source code file of DVR driver

 *

 */

 

#include <avr/io.h>

#include "h-bridge.h"

#include <util/delay.h>

 

//Internal supporting function prototypes

void HBR_initialise();


//function definitions
void HBR_initialise(){
	HBRDDR |= HBR_MASK;

	/*
DRV8821 pin map


#define ONE_ONEN 6 //T1//one plus direction
#define ONE_ONEP 5 //T6
#define ONE_TWON 4 //T2//one neg direction
#define ONE_TWOP 7 //T5

#define TWO_ONEN 2 //T3//two plus direction 
#define TWO_ONEP 1 //T8
#define TWO_TWON 0 //T4//two neg direction
#define TWO_TWOP 3 //T7
*/

	HBRPORT |= (1<< ONE_ONEP) | (1<<ONE_TWOP) | (1<<TWO_ONEP) | (1<<TWO_TWOP);
	HBRPORT &= ~(1<< ONE_ONEN) | ~(1<<ONE_TWON) | ~(1<<TWO_ONEN) | ~(1<<TWO_TWON);
}

void north_out(){
	HBRPORT |= (1<<ONE_ONEN);
	HBRPORT &= ~(1<<ONE_ONEP);//turn on motor
	for (uint8_t i = 0; i < 100; i++){
		_delay_ms(10);
	}
	HBRPORT |= (1<<ONE_ONEP);
	HBRPORT &= ~(1<<ONE_ONEN);//turn off motor


}

void north_in(){
	HBRPORT |= (1<<ONE_TWON);
	HBRPORT &= ~(1<<ONE_TWOP);//turn on motor
	for (uint8_t i = 0; i < 100; i++){
		_delay_ms(10);
	}
	HBRPORT |= (1<<ONE_TWOP);//turn off motor
	HBRPORT &= ~(1<<ONE_TWON);
}

void south_out(){
	HBRPORT |= (1<<TWO_ONEN);
	HBRPORT &= ~(1<<TWO_ONEP);//turn on motor
	for (uint8_t i = 0; i < 100; i++){
		_delay_ms(10);
	}
	HBRPORT |= (1<<TWO_ONEP);
	HBRPORT &= ~(1<<TWO_ONEN);//turn off motor


}

void south_in(){
	HBRPORT |= (1<<TWO_TWON);
	HBRPORT &= ~(1<<TWO_TWOP);//turn on motor
	for (uint8_t i = 0; i < 100; i++){
		_delay_ms(10);
	}
	HBRPORT |= (1<<TWO_TWOP);//turn off motor
	HBRPORT &= ~(1<<TWO_TWON);

}
