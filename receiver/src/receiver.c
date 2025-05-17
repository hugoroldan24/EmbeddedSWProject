#include "spi.h"
#include "radio.h"
#include "pwm.h"
#include "common.h"
#include "pwm_timer0.h"
#include <avr/interrupt.h>

void receiver_config(){
  sei(); /*Set Global Interruptions, from now, we can accept hardware interrupts*/
  SPI_Init();
  RF_Receiver_Init();
  PWM_Init();
  PWM_Timer0_Init();
  PWM_Start();
  PWM_Timer0_Start();
  
  Radio_Listen();
}
  				  
