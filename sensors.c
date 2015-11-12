/****************************************************************

 *            Cool of Engineering Ltd

 *            C212 City Campus, CPIT

 *            (c) CoE, 2015

 *

 *     Filename: STEPPER.c

 *     Developer:Cameron McDonald

 *     Date:    2/11/2015

 *     Description:

 *            Initialise sensors, sat as input, enable pull up resistors

 *

 */

 

#include <avr/io.h>

#include "sensors.h"

#include <util/delay.h>

void sensor_initialise();
uint8_t north_home();
uint8_t south_home();
uint8_t check_switchs(uint8_t current);

void sensor_initialise(){

	SENSOR_DDR = SENSOR_MASK;
	SENSOR_PORT |= (1<<NORTH_HOME) | (1<<SOUTH_HOME);

	SWITCH_DDR = SENSOR_MASK;
	SWITCH_PORT = 0xFF;

	

}

uint8_t north_home(){
	uint8_t home;
	uint8_t home2;
	uint8_t home3;
	while(1){
		home = SENSOR_PIN & (1<<NORTH_HOME);
		_delay_ms(5);
		home2 = SENSOR_PIN & (1<<NORTH_HOME);
		_delay_ms(5);
		home3 = SENSOR_PIN & (1<<NORTH_HOME);
		if (home == home2 && home == home3)
			return home;
		else
			continue;
	}
}

uint8_t south_home(){
	uint8_t home;

	home = SENSOR_PIN & (1<<SOUTH_HOME);
	
	if (home)
		return 0; // not at home
	else
		return 1; // at home
}


uint8_t check_switchs(uint8_t current){//input 0 or 1
	uint8_t switchno;
	
		switchno = SWITCH_PIN & (1<<0);
		if (switchno != current) // check if switch is same as current
			return 0; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<1);
		if (switchno != current) // check if switch is same as current
			return 1; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<2);
		if (switchno != current) // check if switch is same as current
			return 2; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<3);
		if (switchno != current) // check if switch is same as current
			return 3; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<4);
		if (switchno != current) // check if switch is same as current
			return 4; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<5);
		if (switchno != current) // check if switch is same as current
			return 5; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<6);
		if (switchno != current) // check if switch is same as current
			return 6; 	//if it's not, return that switch
		switchno = SWITCH_PIN & (1<<7);
		if (switchno != current) // check if switch is same as current
			return 7; 	//if it's not, return that switch

			//hard coded because or problems with variables in bitwise shift
	
	return 8; //if all good
}
