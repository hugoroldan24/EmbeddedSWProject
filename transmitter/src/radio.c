#include "spi.h"
#include "common.h"



/*-------------------------------------------------------------------------------------------------
Function that initialites all the needed functionatilies from the nRF24L01 to work as a transmitter
-------------------------------------------------------------------------------------------------*/

void init_radio_transmitter(){
  DDRB |= (1 << DD_CE);		          /*Configure pin 0 (will be connected into CE pin the module) as output.*/
  PORTB &= ~(1 << CE_PIN); 		/*Set to 0 just in case*/
  
  _delay_us(10300);                     /*We wait 10.3 ms so that the module has time to reach Power Down state once power is given.*/
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_RF_CH_R);                  /*We send the W_REGISTER instruction with the address of the register we want to modify (RF Channel)*/
  SPI_Send_Data(0x02);                  /*We set the frequency channel at 2.402 GHz to avoid 2.4 GHz Wifi interference*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_RF_SETUP_R);                  /*Instruction to modify the RF Setup Register*/
  SPI_Send_Data(0x0F);                  /*Set Air Data rate to 2 Mbps, RF output power to 0 dB, and set up LNA gain*/
  PORTD |= (1 << SS_PIN);
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_SETUP_AW_R);                  /*Modify SETUP_AW register instruction*/
  SPI_Send_Data(0x03);                  /*Set Address Width to 5 bytes*/
  PORTD |= (1 << SS_PIN);
  
  /*From this point we start to configure the communication protocol from the transmitter side*/
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_SETUP_RETR_R );                  /*Modify the Setup of Retransmission register*/
  SPI_Send_Data(0x00);				   /*Disable retransmission*/                  
  PORTD |= (1 << SS_PIN); 
  
  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(FLUSH_TX);                    /*We send FLUSH_TX to empy the TX_FIFO in case it is not initially empty*/
  PORTD |= (1 << SS_PIN);
}

/*------------------------------------------------------
Function that starts the communication with the receiver
------------------------------------------------------*/

void start_radio_transmitter(){

  PORTD &= ~(1 << SS_PIN);
  SPI_Send_Data(W_CONFIG_R);              /*Instruction to write in the CONFIG register*/
  SPI_Send_Data(0x4A);                    /*Mask interrupt for RX,enable CRC, put PWR_UP = 1 and PRIM_RX = 0 (configure as a TX) */
  PORTD |= (1 << SS_PIN);
  _delay_us(1500);		          /*Start-up delay*/				
  				          /*After the previous setting, we will be in Standby-I state waiting for CE = 1*/
  
  
  PORTB |= (1 << CE_PIN);                 /*Pull CE pin high*/
  _delay_us(4); 		          /*Delay from CE pos.edge to CSN low*/
  
  /*After the previous line, when the TX_FIFO receives data, the transmitter will enter the ephimeral TX Setting state during 130 us and then automatically enter in TX Mode, sending the data through the antenna*/
}	    

