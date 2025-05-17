
#include "spi.h"
#include "pwm.h"
#include "receiver.h"
#include "common.h"
#include <avr/interrupt.h>



extern volatile int8_t availableData;
extern volatile int8_t interrupt_count;
volatile uint16_t converted_valueA = IDLE_STATE;	/*This is the default value when the joysticks are at rest*/
volatile uint16_t converted_valueB = IDLE_STATE;
	
/*---------------------------------------------------------------------------------------------------------------------------------------------------
Main function executed for the receiver microcontroller. The function consists in an infinite loop where ,when habilitated from the ISR, obtains the data from the joysticks using the SPI protocol from the nRF24L01 module
---------------------------------------------------------------------------------------------------------------------------------------------------*/	

int main(void){

  uint8_t ejeX, ejeY;			  /*In this variables we save the joystick value*/
  receiver_config();
  
  while(1){
     	while(!availableData);
	
	PORTD &= ~(1 << SS_PIN);
	SPI_Send_Data(W_STATUS_R); 	  /*Send instruction to write STATUS register*/
	SPI_Send_Data(0x50); 		  /*Cleans the interruption bit RX_DR and MAX_RT*/
	PORTD |= (1 << SS_PIN);
	
	availableData = 0;
	
	PORTD &= ~(1 << SS_PIN);          /*Pull the CSN pin (begin SPI transaccion)*/
	SPI_Send_Data(R_RX_PAYLOAD);      /*Send instruction to read RX_FIFO*/							  
	SPI_Receive_Data(NOP,&ejeX);	  /*Sends dummy data to shift the joystick data from the RF receiver module*/
	SPI_Receive_Data(NOP,&ejeY);	
	PORTD |= (1 << SS_PIN);           /*End SPI transaccion*/
	
	Convert_Value_PWM(ejeX,ejeY,&converted_valueA,&converted_valueB);  /*We set the converted value from the joysticks to the equivalent in OCR1A/OCR1B in the variables converted_valueA/B.*/
     }
   return 0;	
}

  




  //_delay_ms(3000);
  //Convert_Value_PWM(255,255,&converted_valueA,&converted_valueB);  //Giro horario
  //_delay_ms(3000);
  //Convert_Value_PWM(127,127,&converted_valueA,&converted_valueB); //Idle
  //_delay_ms(3000);
  //Convert_Value_PWM(0,0,&converted_valueA,&converted_valueB);//Giro antihorario
  // }
  
  //DDRB |= (1 << DDB5);
  //PORTB |= (1 << PORTB5);
  //_delay_ms(1000);
  //PORTB &= ~(1 << PORTB5);
  //_delay_ms(1000);
  
  
//	while(!availableData);
	
//	availableData = 0;
//	PORTD &= ~(1 << SS_PIN);
//	SPI_Send_Data(W_STATUS_R); 		  /*Send instruction to write STATUS register*/
//	SPI_Send_Data(0x50); 		  /*Cleans the interruption bit RX_DR and MAX_RT*/
//	PORTD |= (1 << SS_PIN);
	
//	PORTD &= ~(1 << SS_PIN);          /*Pull the CSN pin (begin SPI transaccion)*/
//	SPI_Send_Data(R_RX_PAYLOAD); 		  /*Send instruction to read RX_FIFO*/							  
//	SPI_Receive_Data(NOP,&ejeX);	  /*Sends dummy data to shift the joystick data from the RF receiver module*/
//	SPI_Receive_Data(NOP,&ejeY);	
//	PORTD |= (1 << SS_PIN);           /*End SPI transaccion*/
	
//	Convert_Value_PWM(ejeX,ejeY,&converted_valueA,&converted_valueB);  /*We set the converted value from the joysticks to the equivalent in OCR1A/OCR1B in the variables converted_valueA/B.*/
//	}


