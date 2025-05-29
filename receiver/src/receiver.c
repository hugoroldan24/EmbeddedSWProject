#include "spi.h"
#include "radio.h"
#include "pwm.h"
#include "common.h"
#include <avr/interrupt.h>

/*------------------------------------------------------------------------------------------------------------------------
Function that initialices all the receiver functionalities, we configure and start the RF module and start the PWM feature
------------------------------------------------------------------------------------------------------------------------*/
void receiver_config(){

  sei(); /*Set Global Interruptions, from now, we can accept hardware interrupts*/
  
  
  SPI_Init();
 
  PWM_Init();  
  PWM_Timer0_Init();
  
  PWM_Start();

  
  RF_Receiver_Init();
  Radio_Listen();
  
  
}
  				  
