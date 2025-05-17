#include "common.h"
#include "spi.h"
#include <avr/interrupt.h>


volatile int8_t availableData = 0;

/*-----------------------------------------------------------------------
ISR that is triggered when the RF module puts data in the RX_FIFO buffer
------------------------------------------------------------------------*/
ISR(INT0_vect){
	availableData = 1;                  /*Pull the flag so that the main thread can keep executing code*/
	
}

/*--------------------------------------------------
Function that initialices the nRF24L01 as a receiver
--------------------------------------------------*/
void RF_Receiver_Init(){
  uint8_t rx_pipe0_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
  int8_t i;
  
  DDRD &= ~(1 << DD_INT0);               /*Configure INT0 pin (PD2) as input*/
  PORTD |= (1 << INT0_PIN);		 /*Set the pin in Pull-Up mode so that is does not trigger the IRQ wrongly*/
  EICRA |= (1 << ISC01);                 /*Configure INT0 interruption as falling edge trigger (IRQ pin in the RF module is active low)*/ 
  EIMSK |= (1 << INT0);  		 /*Unmask the INT0 interrupt */
  EIFR |= (1 << INTF0);			 /*Clear interrupt request just in case*/
  
  DDRB |= (1<<DD_CE);		          /*Configure pin 0 (will be connected into CE pin the module) as output.*/
  PORTB &= ~(1 << CE_PIN);		  /*Deactivate CE pin just in case*/
  
  _delay_us(10300);			  /*We wait 10.3 ms so that the module has time to reach Power Down state once power is given.*/
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_RF_CH_R);               /*We send the W_REGISTER instruction with the address of the register we want to modify (RF Channel)*/
  SPI_Send_Data(0x02);                    /*We set the frequency channel at 2.402 GHz to avoid 2.4 GHz Wifi interference*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_RF_SETUP_R);            /*Instruction to modify the RF Setup Register*/
  SPI_Send_Data(0x0F);                    /*Set Air Data rate to 2 Mbps, RF output power to 0 dB, and set up LNA gain*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_SETUP_AW_R);            /*Modify SETUP_AW register instruction*/
  SPI_Send_Data(0x03);                    /*Set Address Width to 5 bytes*/
  PORTD |= (1 << SS_PIN);
  
  
  /*Since we will only use Pipe 0, we can deactivate the other 5*/
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_EN_AA_R);               /*Send instruction to write on EN_AA register*/
  SPI_Send_Data(0x00);                    /*Disable all autoacknowledgment in all pipes*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_EN_RXADDR_R);           /*Instruction to write on Enable RX Addresses*/
  SPI_Send_Data(0x01);                    /*Disable all data pipes except pipe 0*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_RX_PW_P0_R);            /*Send instruction to write on RX_PW_P0 register*/
  SPI_Send_Data(0x02);                    /*Set Static Payload to 2 bytes*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(FLUSH_RX);	 	/*Flush RX*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_STATUS_R);		/*Write Status Register*/
  SPI_Send_Data((1<<6));		/*Write 1 to clear the RX_DR bit just in case*/
  PORTD |= (1 << SS_PIN);
  
  
  /*Set the 5 bytes address from the data pipe 0 */
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_RX_ADDR_PO);
  for(i=0;i<5;i++){
     SPI_Send_Data(rx_pipe0_address[i]);
  }
  
  PORTD &= ~(1 << SS_PIN);	    /*Start-up delay*/
  SPI_Send_Data(W_CONFIG_R);        /*Instruction to write in the CONFIG register*/
  SPI_Send_Data(0x3B);              /*Unmask RX_DR interrupt and mask TX_DS and MAX_RTenable CRC, put PWR_UP = 1 and PRIM_RX = 1 (configure as RX) */
  PORTD |= (1 << SS_PIN);
  _delay_us(1500);
 }
 
 /*----------------------------------------------------------
 Function that makes the receiver antenna start to listen
 ----------------------------------------------------------*/
 void Radio_Listen(){
 
  PORTB |= (1<<CE_PIN);		  	  /*Pull CE pin High (this starts after 130 us to listen) */
  				    
 }	    

