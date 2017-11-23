/***************************************************************

Copyright 2015 Arcane Productions

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.



 *           Arcane Productions
 *           (c) AP, 2017
 *
 *
 * 	Filename: stepper.h
 * 	Developer:Cameron McDonald
 * 	Date: 	  11/11/2017
 * 	Description:
 *		Source file of sensor inputs
 *
 *-----------------------------------------------------------*/

 

#ifndef       SENSOR_H
	
#define SENSOR_H

 

#ifndef F_CPU

#define F_CPU 1000000ULL

#endif

#include <util/delay.h>

 

//hardware connections

#define SENSOR_DDR      DDRE

#define SENSOR_PORT     PORTE

#define SENSOR_PIN		PINE

#define SWITCH_DDR		DDRB

#define SWITCH_PORT		PORTB

#define SWITCH_PIN		PINB

 

//pins for STEP ports


#define NORTH_HOME 7
#define NORTH_BACK 5
#define SOUTH_BACK 4
#define SOUTH_HOME 2

 

//mask for CTRL pins

#define SENSOR_MASK 0b00000000

 

//Constants

//#define GLCD_BUSY_FLAG 7

 

//Function prototypes
void sensor_initialise(void);
uint8_t north_home(void);
uint8_t south_home(void);
uint8_t check_switchs(uint8_t current);





#endif
