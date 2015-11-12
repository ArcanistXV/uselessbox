/****************************************************************

 *            Cool of Engineering Ltd

 *            C212 City Campus, CPIT

 *            (c) CoE, 2015

 *

 *     Filename: STEPPER.c

 *     Developer:Cameron McDonald

 *     Date:    2/11/2015

 *     Description:

 *            Source code file of STEPPER driver

 *

 */

 

#include <avr/io.h>

#include "stepper.h"

#include <util/delay.h>

 

//Internal supporting function prototypes
void StepToPos( int intenpos);
void Stepper_initialise();
void Step(uint8_t dir, uint16_t steps);
void North_Step_To_Home_Test();

static int pos;

//function definitions
void Stepper_initialise(){
	STEPA_DDR |= STEPPER_MASK;
	//STEPCD_DDR |= STEPPER_MASK;

	/*

#define ENABLE 	5	//enable active low
#define DIR		4	//dir set
#define STEP	3	//step on rishing edge	
#define RESET	2	//reset
#define MS1		1	//micro step, low - full step, high - half step
#define VDD		0 //logig control, set to HIGH




*/

	STEPA_PORT |= (1<< VDD) | (1<<RESET)|(1<<ENABLE)  | (1<<MS1) ;
	STEPA_PORT &= ~(1<<STEP)|~(1<<DIR);
//	STEPCD_PORT |= (1<<ENBLN) | (1<<RESET); 
//	STEPCD_PORT &= ~(1<<DIR) | (1<<DECAY)| (1<< BUSM0) | (1<<BUSM1);

}

void Step(uint8_t dir, uint16_t steps){
	
	uint8_t delta;
	if (dir == 1){
		STEPA_PORT |= (1<<DIR);
		delta = 1;
		}
	if (dir == 0){
		STEPA_PORT &= ~(1<<DIR);
		delta = -1;
		}
	STEPA_PORT &= ~(1<<ENABLE); //enable stepper output

	for (uint16_t i = 0; i < steps; i++){
		pos += delta;
		STEPA_PORT |= (1<<STEP); // send 1 step
		for (uint8_t i = 0; i < 50; i++)
			_delay_ms(1);
		STEPA_PORT &= ~(1<<STEP); // end 1 step
		for (uint8_t i = 0; i < 50; i++)
			_delay_ms(1);
		if (i > steps) break;
	}


	STEPA_PORT |= (1<<ENABLE); // disable stepper

}

void StepToPos( int intenpos){
	uint8_t delta = 1;
	STEPA_PORT &= ~(1<<ENABLE);
	STEPA_PORT |= (1<<DIR); //direction = 1
	while (pos != intenpos){



		if (intenpos == pos) break;
		/*
		if (intenpos > pos)	{
			delta = 1;
			STEPA_PORT |= (1<<DIR); //direction = 1
		}
		if (intenpos < pos) {
			delta = 1;
			North_Step_To_Home_Test(); //dirty hack
			//delta = -1;
			//STEPA_PORT &= ~(1<<DIR); //dir = 0
		}
		*/
		 //enable stepper output
		pos += delta;
		STEPA_PORT |= (1<<STEP); // send 1 step
		//for (uint8_t i = 0; i < 500; i++)
			_delay_ms(1);
		STEPA_PORT &= ~(1<<STEP); // end 1 step
		//for (uint8_t i = 0; i < 500; i++)
			_delay_ms(1);

	

		}
	STEPA_PORT |= (1<<ENABLE);
}

void North_Step_To_Home(){

	if (north_home() == 1) return;

	STEPA_PORT &= ~(1<<DIR); // set dir to 0
	STEPA_PORT &= ~(1<<ENABLE); // enable stepper
	while(1){
		STEPA_PORT &= ~(1<<DIR); // set dir to 0
		for (uint8_t i = 0; i < 100; i++){
			STEPA_PORT |= (1<<STEP); // send 1 step
			_delay_ms(1);
			STEPA_PORT &= ~(1<<STEP); // end 1 step
			_delay_ms(1);
		}
		if (north_home() == 1){
			_delay_ms(10);
			if (north_home() == 1)//de bounce check
				break;
		}
	} 
	
	STEPA_PORT |= (1<<ENABLE); // disable stepper

}

void North_Step_To_Home_Test(){
	uint8_t home;
	STEPA_PORT &= ~(1<<DIR);

	while(1){
		STEPA_PORT &= ~(1<<ENABLE); //enable stepper output
		STEPA_PORT &= ~(1<<DIR);
		for (uint16_t i = 0; i < 10; i++){
			STEPA_PORT |= (1<<STEP); // send 1 step
			//for (uint8_t i = 0; i < 500; i++)
				_delay_ms(1);
			STEPA_PORT &= ~(1<<STEP); // end 1 step
			//for (uint8_t i = 0; i < 500; i++)
				_delay_ms(1);
		}
	
	home = north_home();
	if (home == 0)//de bounce check
				break;
		

	}
	STEPA_PORT |= (1<<ENABLE); // disable stepper
	pos = 0;
}

void South_Step_To_Home(){
//TODO: change to stepb port
	//if (north_home() == 0) return;
	STEPA_PORT |= (1<<DIR); // set dir to 0
	STEPA_PORT &= ~(1<<ENABLE); // enable stepper
	while(1){
		STEPA_PORT |= (1<<DIR); // set dir to 0
		for (uint8_t i = 0; i < 10; i++){
			STEPA_PORT |= (1<<STEP); // send 1 step
			_delay_ms(5);
			STEPA_PORT &= ~(1<<STEP); // end 1 step
			_delay_ms(5);
		}
		if (north_home() == 1){
			_delay_ms(10);
			if (south_home() == 1){//de bounce check
				_delay_ms(10);
				if (south_home() == 1){//de bounce check
					_delay_ms(10);
					if (south_home() == 1){//de bounce check
						_delay_ms(10);
							if (south_home() == 1)
								break;
						
					}
				}
			}
		}
	} 
	
	STEPA_PORT |= (1<<ENABLE); // disable stepper

}

