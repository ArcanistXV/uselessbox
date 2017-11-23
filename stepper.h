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
 *		Source file of stepper driver
 *
 *-----------------------------------------------------------*/

 

#ifndef       STEPPER_H
	
#define STEPPER_H

 

#ifndef F_CPU

#define F_CPU 1000000ULL

#endif

#include <util/delay.h>


 

//hardware connections

#define STEPA_DDR      DDRA

#define STEPA_PORT     PORTA

#define STEPA_PIN		PINA

 

#define STEPB_DDR      DDRC

#define STEPB_PORT     PORTC

#define STEPB_PIN      PINC


 

//pins for STEP ports


#define SAENABLE 	1	//enable
#define SADIR		2	//dir set
#define SASTEP	3	//step on rising edge	
#define SARESET	4	//reset


#define SAMS1		5	//micro step, low - full step, high - half step
#define SAVDD		6 //logig control, set to HIGH

#define SBENABLE 6
#define SBDIR 5
#define SBSTEP 4
#define SBRESET 3
#define SBMS1 2
#define SBVDD 1

 

//mask for CTRL pins

#define STEPPER_MASK 0b11111111

 

//Constants

//#define GLCD_BUSY_FLAG 7

 

//Function prototypes

void StepToPos( int intenpos);
int Stepper_initialise(void);
void Step(uint8_t dir, uint8_t steps);
void StepB(uint8_t dir, uint8_t steps);
void North_Step_To_Home_Test(void);
void A_Step_To_Home(void);

#endif
