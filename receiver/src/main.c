/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
 
#include "spi.h"
#include "pwm.h"
#include "receiver.h"
#include "common.h"
#include "radio.h"
#include <avr/interrupt.h>


extern volatile int8_t availableData;   /*This flag is activated when the RF module places data in the RX_FIFO register*/
extern volatile int8_t interrupt_count; /*This variable is used to count how many times the Timer0 interrupt is triggered*/
volatile uint16_t servo_A= IDLE_STATE;	/*This is the default value when the joysticks are at rest*/
volatile uint16_t servo_B = IDLE_STATE;
	
/*---------------------------------------------------------------------------------------------------------------------------------------------------
Main function of the receiver.
It waits for the external interrupt triggered by the RF module upon packet reception. Once the interrupt occurs, the joystick data is received via SPI. The values are then processed and mapped to the corresponding OCR1A/B registers to adjust the PWM pulse width accordingly once the Timer0 interrupt is triggered.
---------------------------------------------------------------------------------------------------------------------------------------------------*/	

int main(void){
  uint8_t Xaxis, Yaxis;			  	        /*In this variables we save the joystick values*/
  receiver_config(); 
  while(1){
     while(!availableData);				/*Once the external interrupt connected to the ISR pin in the nrf24 is triggered, we can proceed*/   
     writeRegister(W_STATUS,(1<<RX_DR));    		/*Clear RX_DS flag*/
     get_Received_Data(&ejeX,&ejeY);	    		/*Read RX_FIFO*/ 
     availableData = 0;  
     Convert_Value_PWM(Xaxis,Yaxis,&servo_A,&servo_B);  /*We set the converted value from the joysticks to the equivalent in OCR1A/OCR1B in the variables servo_A/B.*/
     }
   return 0;	
}





