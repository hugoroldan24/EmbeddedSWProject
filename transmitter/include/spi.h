/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
 
#ifndef  SPI_H
#define  SPI_H

#include <stdint.h>
void SPI_Init(void);
void SPI_Send_Data(uint8_t data);
void SPI_Receive_Data(uint8_t dummy, uint8_t* obtainedData);
#endif
