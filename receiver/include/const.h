#ifndef CONST_H
#define CONST_H


//SPI
#define MOSI_PIN  PB3
#define CLK_PIN   PB5
#define MISO_PIN  PB4
#define DD_MOSI   DDB3
#define DD_CLK    DDB5
#define DD_MISO   DDB4
#define DD_SS_SLAVE  DDB2			 	    /*PB2 pin can act as the SS when the Arduino is configured as an Slave*/
#define SS_PIN    PD7				 	    /*This pin has to be connected to the SS from the NRF24L01*/
#define DD_SS     DDD7

//PŴM
#define F_TIMER0 15625UL			  	    /*Timer0 frequency work, note that this value has to match the prescaler set in TCCR0B register*/
#define F_TIMER1 62500UL			  	    /*Timer1 frequency work, note that this value has to match the prescaler set in TCCR1B register*/
#define TIMER0_TIME 5				  	    /*Time we want the Timer0 takes to reach the TOP value (ms)*/
#define TIMER0_PERIOD (TIMER0_TIME*F_TIMER0)/1000 	    /*Number of increments to reach the TOP value*/

/*In general what I am doing in every constant I define in this section, is trying to avoid as much as possible rounding errors*/
/*The operations use the sufix UL so that we avoid overflow*/

#define IDLE_STATE ((3UL*F_TIMER1)/(2UL*1000UL))            /*When setting this value at OCR1A/B , the servomotor won't move*/

#define COUNTER_CLOCKWISE_STATE ((2UL*F_TIMER1)/1000UL)     /*When setting this value at OCR1A/B , the servomotor will move at MAX speed in the specified direction. The 2 comes from the 2ms pulse we want to generate so that the servo spins at max speed in that direction*/

/*The following equation is to generate a value that will produce a 1 ms PWM width pulse. Since we don't work with float numbers, I add 0.5 (multiplied by 1000) so that the final value is rounded to the higher number if >.5 */

#define CLOCKWISE_STATE ((1UL*F_TIMER1+500UL)/1000UL)	    /*When setting this value at OCR1A/B , the servomotor will move at MAX speed in the specified direction*/

/*To convert the ADC values (0, 255) , we will use linear interpolation, OCR1A/B = a +b*ADC, so with the previous constants, we can express 'a' and 'b' in terms of the Timer1 frequency.
Note that if ADC = 0, the servos will have to move max count clockwise , so a = COUNTER_CLOCKWISE_STATE . Then we can find 'b' by doing the same with ADC = 128 , (servo won't move), so b = (OCR1A-a)/ADC */

#define a (COUNTER_CLOCKWISE_STATE * 100UL)

/*Since we are working with UL, when doing the substraction, we can get a negative number, we need to cast the result to a int variable that can manage negative numbers properly*/

#define SUBSTRACTION ((int32_t)(IDLE_STATE) - (int32_t)(COUNTER_CLOCKWISE_STATE))
#define b ((100*SUBSTRACTION)/128) 		/*We multiply by 100 because most likely we will obtain a number <1 and we would then round to 0. Then when executing the respective function, we will divide again by 100.*/

#define PWM_TIME 10			        /*Time we want TIMER1 reach the TOP (ms)*/
#define PWM_PERIOD ((PWM_TIME*F_TIMER1)/1000UL) /*Iterations it will take to reach the TOP (divide by 1000 because the time is in ms*/

#define DD_OC1A	  DDB1			/*PWM pin connected to one servomotor data pin*/
#define DD_OC1B	  DDB2			/*IDEM*/


//NRF24
#define ACTIVATION_KEY 0x73 
#define ADDRESS_WIDTH 5
#define RX_DR 6
#define DD_CE	  DDB0
#define CE_PIN	  PB0
#define DD_INT0	  DDD2
#define INT0_PIN  PD2


//WRITE
#define W_CONFIG 0x20
#define W_SETUP_AW 0x23
#define W_RF_SETUP 0x26
#define W_RF_CH 0x25
#define W_SETUP_RETR 0x24
#define W_STATUS 0x27
#define W_FEATURE 0x3D  /*This command actiaves the NO_ACK feature*/
#define W_EN_AA 0x21
#define W_RX_PW_P0 0x31 
#define W_EN_RXADDR 0x22
#define W_RX_ADDR_PO 0x2A
#define ACTIVATE 0x50 	/*This command followed by the data 0x73 activates the NO_ACK feature*/


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
#define FOSC  16000000UL     /*Clock Speed*/
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1  /*This value is used to configure the Baud Rate of the USART protocol*/ 

#endif
