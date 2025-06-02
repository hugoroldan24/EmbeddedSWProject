/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
 
#include "spi.h"
#include "radio.h"
#include "pwm.h"
#include "common.h"
#include <avr/interrupt.h>

/*--------------------------------------------------------
Function that initialices all the receiver functionalities
--------------------------------------------------------*/

void receiver_config(){
  sei(); 		/*Set Global Interruptions, from now, we can accept hardware interrupts*/
  SPI_Init();		/*Initialice the SPI feature*/
  PWM_Init();  		/*Initialice the PWM feature*/
  PWM_Timer0_Init();	/*Initialice the Timer0*/ 
  PWM_Start();		/*We start generating PWM signals*/
  RF_Receiver_Init();   /*We initialice the RF module as a receiver*/
  Radio_Listen();	/*We start listening for incoming packets*/
}
  				  
