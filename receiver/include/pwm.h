/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
#ifndef PWM_H
#define PWM_H

#include <stdint.h>
void PWM_Init(void);
void PWM_Timer0_Init(void);
void PWM_Start(void);
void Convert_Value_PWM(uint8_t ejeX, uint8_t ejeyY, volatile uint16_t *converted_valueA, volatile uint16_t *converted_valueB);

typedef struct{
   uint16_t sA;
   uint16_t sB;
} Servo;

#endif
