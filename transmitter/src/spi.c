#include "common.h"
#include <avr/interrupt.h>

volatile int8_t spi_tx_done = 0;
volatile uint8_t receivedData;

/*-------------------------------------------------------------------------------------------------------------------------------------------------
ISR that is triggered when an SPI Transaccion is completed. Handling this interrupt turns the SPIF bit back to 0 again. If the received data is not needed, it can be ignored.
--------------------------------------------------------------------------------------------------------------------------------------------------*/

ISR(SPI_STC_vect){
  receivedData = SPDR;							/*We get the data from the reception buffer*/
  spi_tx_done = 1;
}

/*----------------------------------------------------------
Function that initialices the SPI protocol functionality
----------------------------------------------------------*/
void SPI_Init(){
	
  DDRB = DDRB | ((1<<DD_MOSI) | (1<<DD_SS_SLAVE) | (1<<DD_CLK)); /*Set pins as output, DD_SS is the pin (PD7) that is connected to the SS in the module*/ 
  DDRD |= (1<<DD_SS);
  SPCR =  SPCR | ((1<<MSTR) | (1<<SPE));                               /*We configure the arduino as the master and we habilitate the SPI protocol*/
  SPCR = SPCR & ((~(1<<CPOL)) & (~(1<<CPHA)));                         /*We set the Clock Polarity and Phase to 0 */
  SPCR |= (1<<SPIE);						       /*We activate the SPI Transaccion Completed interrupt*/
                                                          
  PORTD |= (1 << SS_PIN);				 	       /*We set the SS_PIN in pull-up mode*/
  /*We don't need to modify the prescaler frequency bits since the restart mode is gives us 4 MHz */
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------
Function that sends an instruction through the SPI protocol. The pin CSN must be pulled down before executing this fuction                      
Parameters:                                                                                                                                     
                 data: Data to be sent                                                                                                          
		 *status RF: Pointer to the variable that saves the data received from the slave                                                
--------------------------------------------------------------------------------------------------------------------------------------------------*/

void SPI_Send_Data(uint8_t data){
  SPDR = data;                                   /*Send data to Slave*/
  while(!spi_tx_done);				 /*Wait until transaccion is completed*/
  spi_tx_done = 0;       
                    		     
}

/*------------------------------------------------------------------------------------------------------
Function that receives data through the SPI protocol. We send dummy data so that the data is shifted back
Parameters:
		dummy: Dummy data to be sent
		*obtainedData: Pointer to a variable where we will save the received data
-------------------------------------------------------------------------------------------------------*/

void SPI_Receive_Data(uint8_t dummy, uint8_t *obtainedData){
  SPDR = dummy;                                   /*Send dummy data to Slave*/
  while(!spi_tx_done);
  spi_tx_done = 0;        			  
  *obtainedData = receivedData;                   
}
