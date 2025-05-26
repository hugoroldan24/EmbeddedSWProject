#include "common.h"
#include "spi.h"
#include <avr/interrupt.h>


volatile int8_t availableData = 0;

/*-----------------------------------------------------------------------
ISR that is triggered when the RF module puts data in the RX_FIFO buffer
------------------------------------------------------------------------*/
ISR(INT0_vect){
   availableData = 1;    /*Pull the flag so that the main thread can keep executing code*/	
}

/*Function that writes the configuration specified into the specified register*/
void writeRegister(uint8_t writeCommand,uint8_t conf){
   PORTD &= ~(1 << SS_PIN);            	
   SPI_Send_Data(writeCommand);
   SPI_Send_Data(conf); 			
   PORTD |= (1 << SS_PIN);
}

/*Function that reads the specified register*/
/*returns: The register configuration       */
uint8_t readRegister(uint8_t reg){
   uint8_t data;
   PORTD &= ~(1 << SS_PIN);            	
   SPI_Send_Data(reg);
   SPI_Receive_Data(NOP,&data); 			
   PORTD |= (1 << SS_PIN);
   return data;
}
/*Send a command to the RF module*/

void sendCommand(uint8_t command){
   PORTD &= ~(1 << SS_PIN);            
   SPI_Send_Data(command); 			
   PORTD |= (1 << SS_PIN);
}
/*Write the address in the specified pipe*/

void writeAddress(uint8_t pipe,uint8_t *addr,uint8_t size){
  int8_t l;
  PORTD &= ~(1 << SS_PIN);				/*Set the 5 bytes address from the transmitter */
  SPI_Send_Data(pipe);
  for(l=0;l<size;l++){
     SPI_Send_Data(addr[l]);
  }
  PORTD |= (1 << SS_PIN);
}

/*--------------------------------------------------
Function that initialices the nRF24L01 as a receiver
--------------------------------------------------*/
void RF_Receiver_Init(){
  uint8_t rx_pipe0_address[] = {0xE7,0xE7,0xE7,0xE7,0xE7};
  
  DDRD &= ~(1 << DD_INT0);               /*Configure INT0 pin (PD2) as input*/
  PORTD |= (1 << INT0_PIN);		 /*Set the pin in Pull-Up mode so that is does not trigger the IRQ wrongly*/
  EICRA |= (1 << ISC01);                 /*Configure INT0 interruption as falling edge trigger (IRQ pin in the RF module is active low)*/ 
  EIFR |= (1 << INTF0);			 /*Clear interrupt request just in case*/
  EIMSK |= (1 << INT0);  		 /*Unmask the INT0 interrupt */
  
  
  DDRB |= (1<<DD_CE);		          /*Configure pin 0 (will be connected into CE pin the module) as output.*/
  PORTB &= ~(1 << CE_PIN);		  /*Deactivate CE pin just in case*/
  
  _delay_us(10300);			   /*We wait 10.3 ms so that the module has time to reach Power Down state once power is given.*/
  
  writeRegister(W_RF_CH,0x04);         	   /*We set the frequency channel at 2.404 GHz to avoid 2.4 GHz Wifi interference*/           	
    
  writeRegister(W_RF_SETUP,0x0F);	   /*Set Air Data rate to 2 Mbps, RF output power to 0 dB, and set up LNA gain*/
  
  writeRegister(W_SETUP_AW,0x03);	
  
  writeRegister(W_EN_AA,0x00);	             /*Since we will only use Pipe 0, we can deactivate the other 5*/
  
  writeRegister(W_EN_RXADDR,0x01);	     /*Disable all data pipes except pipe 0*/
  
  writeRegister(W_RX_PW_P0,0x02);            /*Set Static Payload to 2 bytes in pipe 0*/

  writeRegister(W_STATUS,(1<<6));            /*Clear RX_DS flag just in case was pulled*/
  
  writeAddress(W_RX_ADDR_PO,rx_pipe0_address,ADDRESS_WIDTH); /*Write the address of the pipe 0*/
  
  writeRegister(ACTIVATE,ACTIVATION_KEY);
  
  writeRegister(W_FEATURE,0x01);		 /*We activate the TX_PAYLOAD_NO_ACK feature*/
  
  writeRegister(W_CONFIG,0x3B);
  
  _delay_us(1500);
  
  sendCommand(FLUSH_RX);
 }
 
 /*----------------------------------------------------------
 Function that makes the receiver antenna start to listen
 ----------------------------------------------------------*/
 void Radio_Listen(){
 
  PORTB |= (1<<CE_PIN);		  	/*Pull CE pin High (this starts after 130 us to listen) */
  				    
 }	    
 
 void get_Received_Data(uint8_t *byte1, uint8_t *byte2){
 
   PORTD &= ~(1 << SS_PIN);             /*Pull the CSN pin (begin SPI transaccion)*/
   SPI_Send_Data(R_RX_PAYLOAD);         /*Send instruction to read RX_FIFO*/							  
   SPI_Receive_Data(NOP,byte1);	     	/*Sends dummy data to shift the joystick data from the RF receiver module*/
   SPI_Receive_Data(NOP,byte2);	
   PORTD |= (1 << SS_PIN);    
 
 }

