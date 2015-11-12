/****************************************************************

 *            Cool of Engineering Ltd

 *            C212 City Campus, CPIT

 *            (c) CoE, 2015

 *

 *     Filename: STEPPER.h

 *     Developer:Cameron McDonald

 *     Date:    27/7/2015

 *     Description:

 *            Header file of stepper driver

 *

 */

 

#ifndef       STEPPER_H
	
#define STEPPER_H

 

#ifndef F_CPU

#define F_CPU 16000000ULL

#endif

#include <util/delay.h>

 

//hardware connections

#define STEPA_DDR      DDRE

#define STEPA_PORT     PORTE

#define STEPA_PIN		PINE

 

#define STEPCD_DDR      DDRF

#define STEPCD_PORT     PORTF

#define STEPCD_PIN      PINF

 

//pins for STEP ports


#define ENABLE 	5	//enable
#define DIR		4	//dir set
#define STEP	3	//step on rishing edge	
#define RESET	2	//reset
#define MS1		1	//micro step, low - full step, high - half step
#define VDD		0 //logig control, set to HIGH

 

//mask for CTRL pins

#define STEPPER_MASK 0b11111100

 

//Constants

//#define GLCD_BUSY_FLAG 7

 

//Function prototypes



#endif
