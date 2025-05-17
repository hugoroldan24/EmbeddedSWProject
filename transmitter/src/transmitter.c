#include "adc.h"
#include "spi.h"
#include "delay.h"
#include "common.h"
#include "radio.h"
#include "usart.h"
#include <avr/interrupt.h>

void transmitter_config(){
  
  SPI_Init();
  USART_Init(UBRR);
  Autotrigger_Init();
  ADC_Init();
  sei();
  //init_radio_transmitter();				  
 // start_radio_transmitter();
  start_ADC_conversion();
  
}
