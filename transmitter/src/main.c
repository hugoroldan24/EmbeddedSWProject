
#include "spi.h"
#include "usart.h"
#include "delay.h"
#include "common.h"
#include "transmitter.h"
#include <stdlib.h>

extern volatile int8_t obtainedData;
extern volatile int8_t sendData;
extern volatile int8_t lastChannel;


/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*Main function from the transmitter. It consists of an infinite loop where we send through the SPI protocol to the RF module, the data obtained from the joysticks*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
int main(void){

  uint8_t data_paquet[NUM_ELEMENTS];
  char buf[4];
  
  transmitter_config();			       /*Initialices all the transmitter features*/
  while(1){				       /*Consider that we need to have time to send the whole package before an interrupt is set.*/
    
    while(!sendData);
    sendData = 0;  
    data_paquet[lastChannel] = obtainedData;
    
    if(lastChannel == NUM_ELEMENTS-1){
        PORTD &= ~(1 << SS_PIN);            	/*Chip Select ON*/
    	SPI_Send_Data(0xA0);   			/*Send instruction to write in TX_FIFO*/  
    	PORTD |= (1 << SS_PIN); 	        	/*Chip Select OFF*/
      
    	PORTD &= ~(1 << SS_PIN);            	/*Chip Select ON*/       
    	for(i = 0; i<NUM_ELEMENTS;i++){		/*We send the whole package to the transmitter*/		        
        	SPI_Send_Data(data_paquet[i]);
    	}
    	PORTD |= (1 << SS_PIN); 	        	/*Chip Select off*/   	
     }
   }
    
  return 0;
}

/* CODE FOR DEBUGGING */


  
  /*The following code is for showing the joystick values in the terminal via UART*/
          
    //USART_Send_String("\r\nJoystick X axis: ");
    //itoa(data_paquet[0],bufX,10);	        
    //USART_Send_String(bufX);   
    //USART_Send_String("\r\nJoystick Y axis: ");
    //itoa(data_paquet[1],bufY,10);
    //USART_Send_String(bufY);  
    //USART_Send_String("\n\n\n");
    
    //_delay_ms(250);  
    
    
    
   
