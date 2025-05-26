#ifndef RADIO_H
#define RADIO_H

void RF_Transmitter_Init(void);
void sendPaquet(uint8_t *data,uint8_t size);
void writeRegister(uint8_t writeCommand,uint8_t conf);
void sendCommand(uint8_t command);
void writeAddress(uint8_t pipe,uint8_t *addr,uint8_t size);
uint8_t readRegister(uint8_t reg);

#endif
