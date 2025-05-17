#ifndef PWM_H
#define PWM_H

void PWM_Init(void);
void PWM_Start(void);
void Convert_Value_PWM(uint8_t ejeX, uint8_t ejeyY, volatile uint16_t *converted_valueA, volatile uint16_t *converted_valueB);

#endif
