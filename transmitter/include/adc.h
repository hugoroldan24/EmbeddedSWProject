/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */                                                                  
#ifndef ADC_H
#define ADC_H


#include <stdint.h>

void ADC_Init(void);
void Autotrigger_Init(void);
void start_ADC_conversion(void);

extern volatile int8_t obtainedData; /* Variable where we save the converted data */
extern volatile int8_t sendData;     /* Conversion completed flag */
extern volatile int8_t lastChannel;  /* Last channel that was converted */

#endif


