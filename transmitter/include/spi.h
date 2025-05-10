#ifndef  SPI_H
#define  SPI_H

#include <stdint.h>
void SPI_Init(void);
void SPI_Send_Data(uint8_t data);
void SPI_Receive_Data(uint8_t dummy, uint8_t* obtainedData);
#endif
