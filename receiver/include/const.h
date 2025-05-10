#ifndef CONST_H
#define CONST_H
/*Constantes*/


#define MOSI_PIN  PB3
#define CLK_PIN   PB5
#define MISO_PIN  PB4
#define DD_MOSI   DDB3
#define DD_CLK    DDB5
#define DD_MISO   DDB4
#define DD_SS_SLAVE  DDB2			/*PB2 pin can act as the SS when the Arduino is configured as an Slave*/
					    	/*THIS PIN WHEN CONFIGURED AS AN OUTPUT CAN BE USED AS A GENERAL OUTPUT PIN, SO I WOULD NOT NEED THE DD_SS PIN. BUT SINCE WE USE THE PB2 PIN IN THE RECEIVER (OC1B) I CANT DO THAT FOR NOW*/



#define SS_PIN    PD7			/*This pin has to be connected to the SS from the NRF24L01*/
#define DD_SS     DDD7

#define DD_OC1A	  DDB1
#define DD_OC1B	  DDB2

#define DD_CE	  DDB0
#define CE_PIN	  PB0

#define DD_INT0	  DDD2
#define INT0_PIN  PD2

#define IDLE_STATE 93
#define COUNTER_CLOCKWISE_STATE 125
#define CLOCKWISE_STATE 63

#define PWM_PERIOD 625

#define W_CONFIG_R 0x20
#define W_STATUS_R 0x27
#define FLUSH_RX 0xE2
#define W_RX_PW_P0_R 0x32
#define W_EN_RXADDR_R 0x22
#define W_EN_AA_R 0x21
#define W_SETUP_AW_R 0x23
#define W_RF_SETUP_R 0x26
#define W_RF_CH_R 0x25
#define R_RX_PAYLOAD 0x61
#define NOP 0xFF

#define READ_BIT(reg,bit) (((reg) & (1<<bit)) >> (bit))

#endif
