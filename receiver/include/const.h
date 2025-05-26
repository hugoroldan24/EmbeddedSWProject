#ifndef CONST_H
#define CONST_H



#define MOSI_PIN  PB3
#define CLK_PIN   PB5
#define MISO_PIN  PB4
#define DD_MOSI   DDB3
#define DD_CLK    DDB5
#define DD_MISO   DDB4
#define DD_SS_SLAVE  DDB2			/*PB2 pin can act as the SS when the Arduino is configured as an Slave*/
					    	
#define SS_PIN    PD7			/*This pin has to be connected to the SS from the NRF24L01*/
#define DD_SS     DDD7

#define DD_OC1A	  DDB1
#define DD_OC1B	  DDB2

#define DD_CE	  DDB0
#define CE_PIN	  PB0

#define DD_INT0	  DDD2
#define INT0_PIN  PD2

//PŴM
#define IDLE_STATE 93 			/*When setting this value at OCR1A/B , the servomotor won't move*/
#define COUNTER_CLOCKWISE_STATE 125     /*When setting this value at OCR1A/B , the servomotor will move at MAX speed in the specified direction*/
#define CLOCKWISE_STATE 63		/*When setting this value at OCR1A/B , the servomotor will move at MAX speed in the specified direction*/
#define PWM_PERIOD 625			/*With the specified prescaler, this value is equivalent to 10 ms*/

//RF MODULE
#define ACTIVATION_KEY 0x73 
#define ADDRESS_WIDTH 5
#define RX_DR 6

//WRITE
#define W_CONFIG 0x20
#define W_SETUP_AW 0x23
#define W_RF_SETUP 0x26
#define W_RF_CH 0x25
#define W_SETUP_RETR 0x24
#define W_STATUS 0x27
#define W_FEATURE 0x3D  //This command actiaves the NO_ACK feature
#define W_EN_AA 0x21
#define W_RX_PW_P0 0x31 
#define W_EN_RXADDR 0x22
#define W_RX_ADDR_PO 0x2A
#define ACTIVATE 0x50 	//This command followed by the data 0x73 activates the NO_ACK feature !!



//READ
#define R_RF_CH_R 0x05 
#define R_RF_SETUP_R 0x06
#define R_SETUP_AW_R 0x03
#define R_SETUP_RETR_R 0x04
#define R_CONFIG_R 0x00
#define R_STATUS 0x07
#define R_FEATURE 0x1D
#define R_RX_PAYLOAD 0x61

//COMMAND
#define NOP 0xFF
#define FLUSH_RX 0xE2


//USART
#define FOSC  16000000UL //Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1   

#endif
