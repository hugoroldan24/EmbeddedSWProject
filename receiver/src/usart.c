/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
#include "common.h"
#include <avr/interrupt.h>

/*-------------------------------------------------------------------------------------------------------------------------------------------------
THIS FILE WAS ONLY USED FOR DEBUGGING, FOR EXAMPLE WHEN I NEEDED TO SEE IF THE JOYSTICK VALUES WHERE CORRECT, I USED USART PROTOCOL TO SHOW THEM IN MY LAPTOT TERMINAL 
-------------------------------------------------------------------------------------------------------------------------------------------------*/ 
volatile uint8_t data;
volatile uint8_t ready = 1;	/*At the beginning, we are ready to send data*/

/*-------------------------------------------------------------
ISR that will be triggered everytime the Data Register is empty
-------------------------------------------------------------*/

ISR(USART_UDRE_vect){
   UDR0 = data;		    /*Send data via USART*/
   UCSR0B &= ~(1<<UDRIE0);  /*Deactivate interrupt so that it does not trigger again before we have new data so send*/
   ready = 1;  		    /*Set flag to accept more data*/
}

/*----------------------------------------------
Function that initialites the UART communication
Parameters:
		ubrrn: Baud Rate value
----------------------------------------------*/

void USART_Init(unsigned int ubrrn){
   PRR &= ~(1<<PRUSART0);							    /*Set Baud Rate*/ 
   UBRR0H = (uint8_t)(ubrrn>>8);
   UBRR0L = (uint8_t)(ubrrn);
   UCSR0C &= (~(1<<UMSEL01) & ~(1<<UMSEL00) & ~(1<<USBS0)); /*Set Asynchronous USART and 1 stop bit*/
   UCSR0A &= ~(1<<U2X0); 				    /*Set Asyncrhonous normal mode*/
   /*Set Character Size to 8 bit*/
   UCSR0C |= (1<< UCSZ01) | (1<<UCSZ00);  
   UCSR0B &= ~(1<<UCSZ02);   
   UCSR0B |= (1<<TXEN0);			       	    /*Activate the transmiter*/ 
}

/*-----------------------------------
Function that sends data via USART 
Parameters:
		info: Data to be sent
-----------------------------------*/

void USART_Send(uint8_t info){
     while(!ready);
     ready = 0;	
     data = info;   
     UCSR0B |= (1<<UDRIE0); 				/*Activate interrupt*/   	
}
/*------------------------------------
Functions that send a string via USART
Parameters:
		str: String to be sent
------------------------------------*/

void USART_Send_String(const char* str){
    while(*str){					/*We send all the characters until we arrive to the end \0*/
    	USART_Send(*str++);
	}
}
 
