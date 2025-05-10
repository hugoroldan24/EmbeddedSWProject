#include "spi.h"
#include "radio.h"
#include "pwm.h"
#include "common.h"
#include "pwm_timer0.h"
#include <avr/interrupt.h>

void receiver_config(){
  sei();
  //SPI_Init();
  //init_radio_receiver();
  init_pwm();
  init_pwm_timer0();				  /*Set Global Interruptions, from now, we can accept hardware interrupts*/
  start_pwm();
  start_pwm_timer0();
  //start_radio_listen();
}
