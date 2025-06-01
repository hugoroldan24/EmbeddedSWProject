#include "adc.h"
#include "spi.h"
#include "common.h"
#include "radio.h"
#include <avr/interrupt.h>

/*---------------------------------------------------
Function that configures all the transmitter features
---------------------------------------------------*/
void transmitter_config(){
  sei();		  /*Enable interruprs , from now on, we can accept hardware interrupts*/
  SPI_Init();		  /*Initialice the SPI feature*/
  Autotrigger_Init();     /*Initialice the Autotrigger feature*/
  ADC_Init(); 		  /*Initialice the ADC feature*/
  RF_Transmitter_Init();  /*Initialice the RF module as a transmitter*/		  
  start_ADC_conversion(); /*Start the ADC conversions*/
  
}
