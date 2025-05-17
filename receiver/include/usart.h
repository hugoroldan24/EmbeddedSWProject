#ifndef  USART_H
#define  USART_H

#include <stdint.h>
void USART_Init(unsigned int ubrr);
void USART_Send(uint8_t info);
void USART_Send_String(const char* str);
#endif
