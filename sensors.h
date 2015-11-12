/****************************************************************

 *            Cool of Engineering Ltd

 *            C212 City Campus, CPIT

 *            (c) CoE, 2015

 *

 *     Filename: sensor.h

 *     Developer:Cameron McDonald

 *     Date:    27/7/2015

 *     Description:

 *            Header file of sensor driver

 *

 */

 

#ifndef       SENSOR_H
	
#define SENSOR_H

 

#ifndef F_CPU

#define F_CPU 16000000ULL

#endif

#include <util/delay.h>

 

//hardware connections

#define SENSOR_DDR      DDRF

#define SENSOR_PORT     PORTF

#define SENSOR_PIN		PINF

#define SWITCH_DDR		DDRB

#define SWITCH_PORT		PORTB

#define SWITCH_PIN		PINB

 

//pins for STEP ports


#define NORTH_HOME 0
#define SOUTH_HOME 1

 

//mask for CTRL pins

#define SENSOR_MASK 0b00000000

 

//Constants

//#define GLCD_BUSY_FLAG 7

 

//Function prototypes

uint8_t north_home();
uint8_t south_home();
uint8_t check_switchs(uint8_t current);



#endif
