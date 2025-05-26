#include "common.h"
#include "transmitter.h"
#include "radio.h"


extern volatile int8_t obtainedData;
extern volatile int8_t sendData;
extern volatile int8_t lastChannel;


/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*Main function from the transmitter. It consists of an infinite loop where we send through the SPI protocol to the RF module, the data obtained from the joysticks*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
int main(void){

  uint8_t data_paquet[NUM_ELEMENTS];
 
  transmitter_config();	    /*Initialices all the transmitter features*/
  
  while(1){				       
     while(!sendData);      /*This flag will be set when we convert one ADC channel*/
     sendData = 0;  
     data_paquet[lastChannel] = obtainedData;
    
     if(lastChannel == NUM_ELEMENTS-1) sendPaquet(data_paquet,NUM_ELEMENTS); /*Once all the ADC channels are read, we send the paquet to the RF module*/
  }  
  return 0;
}

