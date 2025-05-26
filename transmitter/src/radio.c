#include "spi.h"
#include "common.h"

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

/*-------------------------------------------------------------------------------------------------
Function that initialites all the needed functionatilies from the nRF24L01 to work as a transmitter
-------------------------------------------------------------------------------------------------*/

void RF_Transmitter_Init(){
  uint8_t tx_address[] = {0xE7,0xE7,0xE7,0xE7,0xE7};
  
  DDRB |= (1 << DD_CE);		          	/*Configure pin 0 (will be connected into CE pin the module) as output.*/
  PORTB &= ~(1 << CE_PIN); 		  	/*Set to 0 just in case*/
  
  _delay_us(10300); 				/*We wait 10.3 ms so that the module has time to reach Power Down state once power is given.*/
  
  writeRegister(W_RF_CH,0x04);         	        /*We set the frequency channel at 2.402 GHz to avoid 2.4 GHz Wifi interference*/           	
    
  writeRegister(W_RF_SETUP,0x0F);		/*Set Air Data rate to 2 Mbps, RF output power to 0 dB, and set up LNA gain*/
  
  writeRegister(W_SETUP_AW,0x03);		/*Set Address Width to 5 bytes*/
  
  writeRegister(W_SETUP_RETR,0x00);	        /*Disable retransmission*/
  
  writeRegister(W_STATUS,0x3E);			/*Delete TX_DS flag and MAX_RT in case they were pulled*/
  
  writeRegister(W_EN_AA,0x00);			/*Disable autoacknowledgment from all pipes*/
  
  writeAddress(W_TX_ADDR,tx_address,ADDRESS_WIDTH); /*You send the write TX address command followed by the address and the number of bytes*/
   
  writeRegister(ACTIVATE,ACTIVATION_KEY);
  
  writeRegister(W_FEATURE,0x01);	 /*We activate the TX_PAYLOAD_NO_ACK feature*/
  
  writeRegister(W_CONFIG,0x5A); 	 /*Mask interrupt for RX,TX,MAX,enable CRC, put PWR_UP = 1 and PRIM_RX = 0 (configure as a TX)*/
  
  _delay_us(1500);		         /*Start-up delay*/				
  				         /*After the previous setting, we will be in Standby-I state waiting for CE = 1*/
  sendCommand(FLUSH_TX);		 /*We flush the TX_FIFO in case it is not empty*/
  				          				         			       
}
  
  				  

/*-----------------------------------------------------------------------------------------------------------------------------------------------
Function that send the package with the joystick data to the module. Since we are working with a loss-tolerant system, we don't need to work with the Auto-ACK and Auto-Retransmit feature, once we send a paquet, the transmitter won't wait for the ACK.
------------------------------------------------------------------------------------------------------------------------------------------------*/


void sendPaquet(uint8_t *data, uint8_t size){
   int8_t i;

   PORTD &= ~(1 << SS_PIN);            	/*Chip Select ON*/
   SPI_Send_Data(W_TX_NO_ACK);   	/*Send instruction to write in TX_FIFO, we don't want to receive an ACK*/    	         	      
   for(i = 0; i<size;i++){		/*We send the whole package to the transmitter*/		        
      SPI_Send_Data(data[i]);
   }
   PORTD |= (1 << SS_PIN); 	        /*Chip Select off*/ 
   
   PORTB |= (1 << CE_PIN);              /*Pull CE pin high to send the paquet*/ 
   _delay_us(15);			/*15 us delay to keep CE PIN HIGH*/
   PORTB &= ~(1 << CE_PIN); 		/*Pull CE pin down to come back to Standby-I when finished with one packet*/
	               	 	
}


    

