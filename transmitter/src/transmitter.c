#include "adc.h"
#include "spi.h"
#include "common.h"
#include "radio.h"
#include <avr/interrupt.h>

/*---------------------------------------------------
Function that configures all the transmitter features
---------------------------------------------------*/
void transmitter_config(){
  sei();
  SPI_Init();
  Autotrigger_Init();
  ADC_Init();
  RF_Transmitter_Init();				  
  start_ADC_conversion();
  
}
