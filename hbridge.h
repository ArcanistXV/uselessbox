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
 *		Source file of h bridge driver
 *
 *-----------------------------------------------------------*/

 

#ifndef       HBR_H
	
#define HBR_H

 

#ifndef F_CPU

#define F_CPU 1000000ULL

#endif

#include <util/delay.h>

 

//hardware connections

#define HBRDDR      DDRD

#define HBRPORT     PORTD

#define HBRPIN		PIND



// 0 -NC 1 - A EN 2 - Aforward, 3 - A backwards, 4  - BEN, 5 - B Forwards, 6 - B Backwards, 7 - NC

#define ONE_FORWARDS 0b00000110
#define ONE_BACKWARDS 0b00001010
#define TWO_FORWARDS 0b00110000
#define TWO_BACKWARDS 0b01010000
#define ALL_OFF 0b00000000
 
/*
//pins for STEP ports
// micro out 1 to 8, 2 to 6,3 to 4, 4to 2,5to 1,6 to 3, 7 to 5, 8 to 7
//pair 1 forward = pins 8 and 5,backward = pins 6and 7
//tomake it go forward pin8 must be low, pin 7 must be high
#define ONE_ONEN 0 //T5//one plus direction
#define ONE_ONEP 6 //T2
#define ONE_FORWARD_MASK 0b01001110
//to make it go backwards pin2 must be low,  pin 8 must be high
#define ONE_TWON 1 //T6//one neg direction
#define ONE_TWOP 7 //T1
#define ONE_BACKWARD_MASK 0b10001101
//motor two
//forward must be 4 low, 5 high
#define TWO_ONEN 2 //T7//two plus direction 
#define TWO_ONEP 4 //T4
#define TWO_FORWARD_MASK 0b00011011
//backwards pins 4 low pin 6
#define TWO_TWON 3 //T8//two neg direction
#define TWO_TWOP 5 //T3
#define TWO_BACKWARD_MASK 0b00100111

//mask for CTRL pins
//all off
#define ALL_OFF 0b00001111
#define HBR_MASK 0b11111111

 */

//Constants

//#define GLCD_BUSY_FLAG 7

 

//Function prototypes



#endif
