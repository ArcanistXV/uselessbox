/****************************************************************

 *            Cool of Engineering Ltd

 *            C212 City Campus, CPIT

 *            (c) CoE, 2015

 *

 *     Filename: h-bridge.h

 *     Developer:Cameron McDonald

 *     Date:    27/7/2015

 *     Description:

 *            Header file of H bridge driver

 *

 */

 

#ifndef       HBR_H
	
#define HBR_H

 

#ifndef F_CPU

#define F_CPU 16000000ULL

#endif

#include <util/delay.h>

 

//hardware connections

#define HBRDDR      DDRA

#define HBRPORT     PORTA

#define HBRPIN		PINA


 

//pins for STEP ports


#define ONE_ONEN 6 //T1//one plus direction
#define ONE_ONEP 5 //T6
#define ONE_TWON 4 //T2//one neg direction
#define ONE_TWOP 7 //T5

#define TWO_ONEN 2 //T3//two plus direction 
#define TWO_ONEP 1 //T8
#define TWO_TWON 0 //T4//two neg direction
#define TWO_TWOP 3 //T7
 

//mask for CTRL pins

#define HBR_MASK 0b11111111

 

//Constants

//#define GLCD_BUSY_FLAG 7

 

//Function prototypes



#endif
