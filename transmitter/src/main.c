#include "common.h"
#include "transmitter.h"
#include "radio.h"


extern volatile int8_t obtainedData; /*Variable where we save the converted data*/
extern volatile int8_t sendData;     /*Conversion completed flag*/
extern volatile int8_t lastChannel;  /*Last channel that we have converted*/


/*------------------------------------------------------------------------------------------------------------------------------------------------
Main function of the transmitter.
It consists of an infinite loop that sends data obtained from the joysticks to the RF module via the SPI protocol.

The workflow is as follows: after transmitter_config() is executed, Timer1 starts counting and triggers ADC conversions. When the ADC Conversion Complete ISR is triggered, the resulting value is stored in the appropriate position of the data_paquet array.

Once both channels have been converted (lastChannel == NUM_ELEMENTS - 1), the sendPaquet() function is called. This function sends the data to the RF module, which assembles the packet and transmits it wirelessly to the receiver.
--------------------------------------------------------------------------------------------------------------------------------------------------*/

int main(void){
  uint8_t data_paquet[NUM_ELEMENTS];
  transmitter_config();	   	 /*Initialices all the transmitter features*/
  while(1){				       
     while(!sendData);           /*This flag will be set when we convert one ADC channel*/
     sendData = 0;  
     data_paquet[lastChannel] = obtainedData;
    
     if(lastChannel == NUM_ELEMENTS-1) sendPaquet(data_paquet,NUM_ELEMENTS); /*Once all the ADC channels are read, we send the paquet to the RF module*/
  }  
  return 0;
}

