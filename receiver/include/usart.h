/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
#ifndef  USART_H
#define  USART_H

#include <stdint.h>
void USART_Init(unsigned int ubrr);
void USART_Send(uint8_t info);
void USART_Send_String(const char* str);
#endif
