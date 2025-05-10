#ifndef PWM_H
#define PWM_H

void init_pwm(void);
void start_pwm(void);
void Convert_Value_PWM(uint8_t ejeX, uint8_t ejeyY, volatile uint16_t *converted_valueA, volatile uint16_t *converted_valueB);

#endif
