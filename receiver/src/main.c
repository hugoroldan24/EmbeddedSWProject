
#include "spi.h"
#include "pwm.h"
#include "receiver.h"
#include "common.h"
#include "radio.h"
#include <avr/interrupt.h>


extern volatile int8_t availableData;
extern volatile int8_t interrupt_count;
volatile uint16_t servo_A= IDLE_STATE;	/*This is the default value when the joysticks are at rest*/
volatile uint16_t servo_B = IDLE_STATE;
	
/*---------------------------------------------------------------------------------------------------------------------------------------------------
Main function executed for the receiver microcontroller. The function consists in an infinite loop where ,when habilitated from the ISR, obtains the data from the joysticks using the SPI protocol from the nRF24L01 module
---------------------------------------------------------------------------------------------------------------------------------------------------*/	

int main(void){

  uint8_t ejeX, ejeY;			  /*In this variables we save the joystick values*/
 
  receiver_config();
  while(1){
     while(!availableData);
     writeRegister(W_STATUS,(1<<RX_DR));    /*Clear RX_DS flag*/
     get_Received_Data(&ejeX,&ejeY);	    /*Read RX_FIFO*/ 
     availableData = 0;
/*We set the converted value from the joysticks to the equivalent in OCR1A/OCR1B in the variables servo_A/B.*/
     Convert_Value_PWM(ejeX,ejeY,&servo_A,&servo_B); 
     }
   return 0;	
}





