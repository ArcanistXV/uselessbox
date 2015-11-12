/*
DRV8821 pin map

1-ABSTEP
2-ABUSM0
3-ABDIR
4-ABENBLN
5-ABUSM1
6-ABRESETN
7-ABDECAY



*/

/*------------------------------------------------------------- 
 * 			Cool of Engineering Ltd
 * 			C212 City Campus, CPIT 
 * 			(c) CoE, 2015 
 * 
 * 	Filename: rtc.c
 * 	Developer:Cameron McDonald
 * 	Date: 	  25/8/2015 
 * 	Description: 
 *		Source file of main file for useless box project
 * 
 *-----------------------------------------------------------*/


#include <avr/io.h>

#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "h-bridge.h"
#include "stepper.h"
 //SW 1 280
 //SW 2 340


//declare global variables



 int main(){
	
	int swNpos[8] = {425, 525, 620, 700, 780, 880, 960, 1040};
	int i = 0;
	uint8_t switcha;
	HBR_initialise();
	Stepper_initialise();
	sensor_initialise();


	North_Step_To_Home_Test();
	
	
	//sleep(500);
	
	while(1){
		
		if (north_home() == 1){
			North_Step_To_Home_Test();
			}
			
		while (north_home() == 0 && check_switchs(0) == 8){
			//sleep

			sleep(1000);
			switcha = check_switchs(0);
			if (switcha != 8)
				break;

		}

		if (switcha != 8){
			STEPA_PORT |= (1<<DIR); // set dir to 1
			StepToPos(swNpos[switcha]);
		}
		sleep(250);
		north_in();
		sleep(500);
		north_out();
		STEPA_PORT &= ~(1<<DIR); // set dir to 0
		North_Step_To_Home_Test();


	}

	
	//Step(1, 300);
	//north_out();
	//north_in();
	
while(1);
	//while(1); //end

}


void sleep(int ms){
	
	for (int i = 0; i < ms; i++){
		 _delay_ms(1);
		}
}
 
