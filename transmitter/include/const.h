#ifndef CONST_H
#define CONST_H


//SPI
#define SS_PIN    PD7				/*This pin has to be connected to the SS from the NRF24L01*/
#define DD_SS     DDD7 
#define DD_SS_SLAVE  DDB2			/*PB2 pin can act as the SS when the Arduino is configured as an Slave*/
#define MOSI_PIN  PB3
#define CLK_PIN   PB5
#define MISO_PIN  PB4
#define DD_MOSI   DDB3
#define DD_CLK    DDB5
#define DD_MISO   DDB4


#define NUM_ELEMENTS 2			  	/*Number of motors we want to control*/

//ADC

#define F_AUTO_TRIGGER 2 	 /*Autotrigger timer frequency work, note that this value has to match the prescaler set in TCCR1B register*/
				 /*For convenience, I express the value in increments/us , it will be easier for calculating the autotrigger period*/
				
				 				 
#define AUTO_TRIGGER_TIME 3000  /*Time between each autotrigger pulse (time between ADC conversions) in us*/
#define AUTO_TRIGGER_PERIOD AUTO_TRIGGER_TIME*F_AUTO_TRIGGER /*Take care when setting values that gives a float number (it will be truncated)*/
#define pinX1     PC0
#define pinY1     PC1
#define pinX2     PC2
#define pinY2     PC3
#define ADMUX_MUX 15 

//NRF24
#define DD_CE	  DDB0
#define CE_PIN	  PB0
#define ADDRESS_WIDTH 5
#define ACTIVATION_KEY 0x73

//WRITE
#define W_CONFIG 0x20
#define W_SETUP_AW 0x23
#define W_RF_SETUP 0x26
#define W_RF_CH 0x25
#define W_SETUP_RETR 0x24
#define W_STATUS 0x27
#define W_FEATURE 0x3D 
#define W_EN_AA 0x21
#define W_TX_ADDR 0x30

//COMMANDS
#define W_TX_FIFO 0xA0
#define W_TX_NO_ACK 0xB0
#define FLUSH_TX 0xE1
#define ACTIVATE 0x50 
#define NOP 0xFF

//READ
#define R_RF_CH_R 0x05 
#define R_RF_SETUP_R 0x06
#define R_SETUP_AW_R 0x03
#define R_SETUP_RETR_R 0x04
#define R_TX_ADDR 0x10
#define R_CONFIG_R 0x00
#define R_STATUS 0x07
#define R_FEATURE 0x1D


//USART
#define FOSC  16000000UL /*Clock Speed*/
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1   

#endif
