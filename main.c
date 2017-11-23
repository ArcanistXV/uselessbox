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
 * 	Filename: main.c
 * 	Developer:Cameron McDonald
 * 	Date: 	  11/11/2017
 * 	Description:
 *		Source file of main file for useless box project
 *
 *-----------------------------------------------------------*/
#include <asf.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include "stepper.h"
#include "hbridge.h"
#include "sensors.h"


uint32_t positionA[] = {150, 240, 330, 425, 510, 600, 690, 780};
uint32_t switches[] = {0,0,0,0,0,0,0,0};
uint32_t positionB[] = {825,735,635,555,455,370,280,180};
const uint32_t ARM_PRESS_DELAY = 80; //arm press/4
const uint32_t ARM_WITHDRAW_DELAY = 200;
	
uint8_t Ndir = 0;
uint8_t Sdir = 0;
uint8_t direction = 0;
uint8_t total_direction;
uint8_t steps = 1;
uint32_t Nhome;
uint32_t Shome;
uint8_t swap;
uint8_t current_switch;
uint8_t failflagA = 0;
uint8_t failflagB = 0;
uint8_t resetflagA = 0;
uint8_t resetflagB = 0;
uint8_t startup = 1;
		
uint32_t currentApos;
uint32_t currentBpos;
uint32_t targetApos = 0;
uint32_t targetBpos = 0;	
uint32_t timerflag = 0;
uint32_t i = 0;
uint8_t kiki = 1;
int main (void)
{	

		wdt_disable();
        DDRA = 0b11111111;
		PORTA = 0b01110100;// MS enables
		
		DDRC = 0b11111111;
		PORTC = 0b00101110;
		
		DDRD = 0b11111111; //HB port
		PORTD = ALL_OFF;
		
		DDRB = 0x00; //switchs
		PORTB = 0xFF;
		DDRE = 0x00;
		PORTE = 0b11111100;


		_delay_ms(10);
		
		//0 = 185, 1 = 275,2 = 365, 3 = 455, 4 = 455
		
	kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
	
	
	/*		//if ((SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK){//ensure north is back
				kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
				while (kiki){
					PORTD = ONE_FORWARDS;
					_delay_ms(25);
					kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
					PORTD = ALL_OFF;
					_delay_ms(ARM_WITHDRAW_DELAY);
				}
			//	}
				
			//	if ((SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK){//ensure south is back
					kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
					while (kiki){
						PORTD = TWO_FORWARDS;
						_delay_ms(25);
						kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
						PORTD = ALL_OFF;
						_delay_ms(ARM_WITHDRAW_DELAY);
					}
			//	}
		*/		

	while(1){
		
		Nhome = SENSOR_PIN & (1<<NORTH_HOME);
		/*	kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
		while (kiki){
			PORTD = ONE_FORWARDS;
			_delay_ms(25);
			kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
			PORTD = ALL_OFF;
			_delay_ms(ARM_WITHDRAW_DELAY);
		}*/
		if (resetflagA == 1 || startup){
			resetflagA = 0;
			if (Nhome >> NORTH_HOME){
				while((STEPA_PORT & (1<<SAENABLE)) >> SAENABLE)
					STEPA_PORT &= ~(1<<SAENABLE); //enable stepper
				timerflag = 0;
				while(Nhome >> NORTH_HOME){//step to home
					timerflag++;
					if (timerflag > 850){ // try to move in other dir and withdraw arm
						for (uint8_t l = 0; l < 2; l++){
							for (uint8_t j = 0; j < 75; j++){
								STEPA_PORT |= (1<<SADIR); // set dir to 1
								_delay_ms(1);
								STEPA_PORT |= (1<<SASTEP); // send 1 step
								_delay_ms(1);
								STEPA_PORT &= ~(1<<SASTEP); // end 1 step
								_delay_ms(1);
							}
							for (uint8_t f = 0; f < 3; f++){
								PORTD = ONE_FORWARDS;
								_delay_ms(100);
								PORTD = ALL_OFF;
								_delay_ms(100);
							}
							timerflag = 0;
							timerflag = 1;
							timerflag = 0;
						}
					}
					STEPA_PORT &= ~(1<<SADIR); // set dir to 0
					STEPA_PORT |= (1<<SASTEP); // send 1 step
					_delay_ms(1);
					STEPA_PORT &= ~(1<<SASTEP); // end 1 step
					_delay_ms(1);
					Nhome = SENSOR_PIN & (1<<NORTH_HOME);
					if ((Nhome >> NORTH_HOME) == 0)
						currentApos = 0;
				}
				STEPA_PORT |= (1<<SAENABLE); //disable stepper
			}
		}
		if (resetflagB == 1 || startup == 1){
			startup = 0;
			resetflagB = 0;
			Shome = SENSOR_PIN & (1<<SOUTH_HOME);
			currentBpos = 0;
		/*	kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
				while (kiki){
					PORTD = TWO_FORWARDS;
					_delay_ms(25);
					kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
					PORTD = ALL_OFF;
					_delay_ms(ARM_WITHDRAW_DELAY);
				}*/
		
			if (Shome >> SOUTH_HOME){
				STEPB_PORT &= ~(1<<SBENABLE); //enable stepper
				timerflag = 0;
				while(Shome >> SOUTH_HOME){//step to home
					timerflag++;
					if (timerflag > 850){ // try to move in other dir and withdraw arm
						for (uint8_t l = 0; l < 2; l++){
							for (uint8_t j = 0; j < 75; j++){
								STEPB_PORT |= (1<<SBDIR); // set dir to 0
								STEPB_PORT |= (1<<SBSTEP); // send 1 step
								_delay_ms(1);
								STEPB_PORT &= ~(1<<SBSTEP); // end 1 step
								_delay_ms(1);
							}
							for (uint8_t f = 0; f < 3; f++){
								PORTD = TWO_FORWARDS;
								_delay_ms(100);
								PORTD = ALL_OFF;
								_delay_ms(100);
							}
							timerflag = 0;
							timerflag = 1;
							timerflag = 0;
						}
					}
					STEPB_PORT &= ~(1<<SBDIR); // set dir to 0
					STEPB_PORT |= (1<<SBSTEP); // send 1 step
					_delay_ms(1);
					STEPB_PORT &= ~(1<<SBSTEP); // end 1 step
					_delay_ms(1);
					Shome = SENSOR_PIN & (1<<SOUTH_HOME);
					if ((Shome >> SOUTH_HOME) == 0)
						currentBpos = 0;
				}
				STEPB_PORT |= (1<<SBENABLE); //disable stepper
			}
		}
		
		if (failflagA == 0 && failflagB == 0){ //if last press was not a fail
			direction = 2;
		
			for (i = 0; i < 8; i++){
				swap = PINB & (1<<i);
				switches[i] = (swap >> i);
			}
			total_direction = 0;
			for (i = 0; i < 8; i++){
				total_direction += switches[i];
			}
			if (total_direction < 4)
				direction = 0; 
			if (total_direction > 3)
				direction = 1;
			if (total_direction == 0 || total_direction == 8)
				continue; //all are same
			for (i = 0; i < 8; i++){
				if (switches[i] != direction && direction == 1){
					_delay_ms(10);//debounce check
					swap = PINB & (1<<i);
					if ((swap >> i) != direction){
						targetApos = positionA[i];
						current_switch = i;
						break;
					}	
				}
				if (switches[i] != direction && direction == 0){
					_delay_ms(10);//debounce check
					swap = PINB & (1<<i);
					if ((swap >> i) != direction){
						targetBpos = positionB[i];
						current_switch = i;
						break;
					}
				}
			}
		}
		
		
		if (direction == 1){
		/*	kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
			while (kiki){
				PORTD = ONE_FORWARDS;
				_delay_ms(25);
				kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
				PORTD = ALL_OFF;
				_delay_ms(ARM_WITHDRAW_DELAY);
			}*/
			PORTD = ONE_FORWARDS;
			_delay_ms(100);
			PORTD = ALL_OFF;
			STEPA_PORT &= ~(1<<SAENABLE); //enable stepper
			while (currentApos != targetApos){
				
				if (currentApos < targetApos || currentApos == 0){
					Ndir = 1;
					STEPA_PORT |= (1<<SADIR);
					_delay_ms(1);
				}
				if (currentApos > targetApos){
					Ndir = 2;
					STEPA_PORT &= ~(1<<SADIR);
					_delay_ms(1);
				}
			
				STEPA_PORT |= (1<<SASTEP); // send 1 step
				_delay_ms(1);
				STEPA_PORT &= ~(1<<SASTEP); // end 1 step
				_delay_ms(1);
				if (Ndir==1)
					currentApos++;
				if (Ndir==2)
					currentApos--;	
			}
			STEPA_PORT |= (1<<SAENABLE); //disable stepper
			_delay_ms(1);
			for (i = 0; i < 5; i++){
				PORTD = ONE_BACKWARDS;//press lever
				for (uint8_t s = 0; s < 4; s++)
						_delay_ms(ARM_PRESS_DELAY);
				PORTD = ONE_FORWARDS;
				_delay_ms(100);
				PORTD = ALL_OFF;
				swap = PINB & (1<<current_switch);//check if switch is flicked
				if ((swap >> current_switch) == direction){
					failflagA = 0;
					if (positionA[current_switch] != currentApos)
						positionA[current_switch] = currentApos;
					PORTD = ONE_FORWARDS; //return again
					_delay_ms(100);
					PORTD = ALL_OFF;
					break;
				}
					
				
			}
				
			

			/*	kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
			while (kiki){
				PORTD = ONE_FORWARDS;
				_delay_ms(25);
				kiki = (SENSOR_PIN & (1<<NORTH_BACK)) >> NORTH_BACK;
				PORTD = ALL_OFF;
				_delay_ms(ARM_WITHDRAW_DELAY);
			}*/
			PORTD = ONE_FORWARDS;
			_delay_ms(100);
			PORTD = ALL_OFF;
			swap = PINB & (1<<current_switch);
			if ((swap >> current_switch) != direction){
				if (failflagA == 3){
					for (uint32_t wait = 0; wait < 50; wait++){
						_delay_ms(200);
						}
					failflagA = 0;
					resetflagA = 1;
					break;
				}
				if (failflagA == 1){
					targetApos += 10;
					failflagA = 2;
				}
				if (failflagA == 2){
					targetApos -=20;
					failflagA = 3;
				}
				if (failflagA == 0){//TODO
					failflagA = 1;
				}
				break;
			}
		}
		
		
		if (direction == 0){
			PORTD = ALL_OFF;
			PORTD = TWO_FORWARDS;
			_delay_ms(100);
			PORTD = ALL_OFF;
		/*	kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
			while (kiki){
				PORTD = TWO_FORWARDS;
				_delay_ms(25);
				kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
				PORTD = ALL_OFF;
				_delay_ms(ARM_WITHDRAW_DELAY);
			}*/
			while((STEPB_PORT & ~(1<<SBENABLE)) >> SBENABLE)
				STEPB_PORT &= ~(1<<SBENABLE); //enable stepper
			while (currentBpos != targetBpos){
				if (currentBpos < targetBpos){
					
					STEPB_PORT |= (1<<SBDIR);
					Sdir = 1;
				}
				if (currentBpos > targetBpos){
					
					STEPB_PORT &= ~(1<<SBDIR);
					Sdir = 2;
				}
				_delay_us(300);
				STEPB_PORT |= (1<<SBSTEP); // send 1 step
				_delay_ms(1);
				STEPB_PORT &= ~(1<<SBSTEP); // end 1 step
				_delay_ms(1);
				if (Sdir==1)
					currentBpos++;
				if (Sdir==2)
					currentBpos--;	
			}
		
			STEPB_PORT |= (1<<SBENABLE); //disable stepper
			_delay_ms(1);
			for (i = 0; i < 5; i++){
				PORTD = TWO_BACKWARDS;//press lever
				for (uint8_t s = 0; s < 4; s++)
						_delay_ms(ARM_PRESS_DELAY);
				PORTD = TWO_FORWARDS;
				_delay_ms(100);
				PORTD = ALL_OFF;
				swap = PINB & (1<<current_switch);
				if ((swap >> current_switch) == direction){
					failflagB = 0;
					if (positionB[current_switch] != currentBpos)
						positionB[current_switch] = currentBpos;
					PORTD = TWO_FORWARDS;
					_delay_ms(100);
					PORTD = ALL_OFF;
					break;		
				}
			}
			/*	kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
			while (kiki){
				PORTD = TWO_FORWARDS;
				_delay_ms(25);
				kiki = (SENSOR_PIN & (1<<SOUTH_BACK)) >> SOUTH_BACK;
				PORTD = ALL_OFF;
				_delay_ms(ARM_WITHDRAW_DELAY);
			}*/
			PORTD = TWO_FORWARDS;
			_delay_ms(100);
			PORTD = ALL_OFF;
			
			swap = PINB & (1<<current_switch);
			if ((swap >> current_switch) != direction){
				if (failflagB == 3){//arm totally has failed
					for (uint32_t wait = 0; wait < 50; wait++){
						_delay_ms(200);
					}
					failflagB = 0;
					resetflagB = 1;
				}
				if (failflagB == 2){
					targetBpos -=20;
					failflagB = 3;
				}
				if (failflagB == 1){
					targetBpos += 10;
					failflagB = 2;
				}
				
				if (failflagB == 0){//TODO
					failflagB = 1;
				}
				break;
			}
		}
	}
}