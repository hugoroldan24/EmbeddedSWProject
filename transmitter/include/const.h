#ifndef CONST_H
#define CONST_H
/*Constantes*/

#define SS_PIN    PD7				/*This pin has to be connected to the SS from the NRF24L01*/
#define DD_SS     DDD7 

#define DD_SS_SLAVE  DDB2			/*PB2 pin can act as the SS when the Arduino is configured as an Slave*/

#define MOSI_PIN  PB3
#define CLK_PIN   PB5
#define MISO_PIN  PB4
#define DD_MOSI   DDB3
#define DD_CLK    DDB5
#define DD_MISO   DDB4

#define pinX1     PC0
#define pinY1     PC1
#define pinX2     PC2
#define pinY2     PC3
#define ADMUX_MUX 15 

#define DD_CE	  DDB0
#define CE_PIN	  PB0

#define READ_BIT(reg,bit) (((reg) & (1<<bit)) >> (bit))
#define NUM_ELEMENTS 2			  	/*Number of motors we want to control*/

#define AUTO_TRIGGER_PERIOD 6000   /*With the ADC prescaler configured, this value defines the ms it takes to reach the TOP value.*/


#define W_CONFIG_R 0x20
#define W_SETUP_AW_R 0x23
#define W_RF_SETUP_R 0x26
#define W_RF_CH_R 0x25
#define W_SETUP_RETR_R 0x24
#define W_TX_ADDR 0x30
#define W_TX_FIFO 0xA0
#define FLUSH_TX 0xE1


#define FOSC  16000000UL //Clock Speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1   

#endif
