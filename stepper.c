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

 #ifndef F_CPU

 #define F_CPU 1000000ULL

 #endif

#include <avr/io.h>

#include "STEPPER.h"
//#include "sensors.h"

#include <util/delay.h>

 

//Internal supporting function prototypes
void StepToPos( int intenpos);
int Stepper_initialise(void);
void Step(uint8_t dir, uint8_t steps);
void StepB(uint8_t dir, uint8_t steps);
void North_Step_To_Home_Test(void);
void A_Step_To_Home(void);
uint8_t main(void);

static int posA;
static int posB;

//function definitions
int Stepper_initialise(){
	DDRA = 0b11111111;
	PORTA = 0b01010100;
	
	DDRC = 0b11111111;
	PORTC = 0b00101010;
	//STEPCD_DDR |= STEPPER_MASK;

/*
	STEPA_PORT |= (1<< SAVDD) | (1<<SARESET) | (1<<SAMS1)  ;
	STEPA_PORT &= ~(1<<SASTEP)|~(1<<SADIR)| ~(1<<SAENABLE);
	*/

	return 1;
}

void Step(uint8_t dir, uint8_t steps){
		uint8_t delta;
	if (dir == 1){
		STEPA_PORT |= (1<<SADIR);
		delta = 1;
	}
	if (dir == 0){
		STEPA_PORT &= ~(1<<SADIR);
		delta = -1;
	}
	STEPA_PORT &= ~(1<<SAENABLE); //enable stepper output

	for (uint8_t s = 0; s < steps; s++){
			STEPA_PORT |= (1<<SASTEP); // send 1 step
				_delay_ms(1);
			STEPA_PORT &= ~(1<<SASTEP); // end 1 step
				_delay_ms(1);				
	}
	STEPA_PORT |= (1<<SAENABLE); // disable stepper
	
}

void StepB(uint8_t dir, uint8_t steps){
	
	uint8_t delta;
	if (dir == 1){
		STEPB_PORT |= (1<<SBDIR);
		delta = 1;
	}
	if (dir == 0){
		STEPB_PORT &= ~(1<<SBDIR);
		delta = -1;
	}
	STEPB_PORT |= (1<<SBENABLE); //enable stepper output

	for (uint16_t i = 0; i < steps; i++){
		posB += delta;
		STEPB_PORT |= (1<<SBSTEP); // send 1 step
		//for (uint8_t i = 0; i < 10; i++)
		//_delay_ms(1);
		STEPB_PORT &= ~(1<<SBSTEP); // end 1 step
		//for (uint8_t i = 0; i < 10; i++)
		//_delay_ms(1);
		if (i > steps) break;
	}


	STEPB_PORT |= (1<<SBENABLE); // disable stepper
	return;
}
/*
void A_Step_To_Home(){

	if (north_home() == 1) return;

	STEPA_PORT &= ~(1<<SADIR); // set dir to 0
	STEPA_PORT &= ~(1<<SAENABLE); // enable stepper
	while(1){
		STEPA_PORT &= ~(1<<SADIR); // set dir to 0
		Step(0, 10);
		if (north_home() == 1){
			_delay_ms(10);
			if (north_home() == 1)//de bounce check
			break;
		}
	}
	
	STEPA_PORT |= (1<<SAENABLE); // disable stepper

}


/*
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
*/

