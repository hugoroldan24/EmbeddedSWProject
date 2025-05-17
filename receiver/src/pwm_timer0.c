#include "common.h"
#include <avr/interrupt.h>

extern volatile uint16_t converted_valueA;
extern volatile uint16_t converted_valueB;
volatile int8_t interrupt_count = 0;

ISR(TIMER0_COMPA_vect){
	if(++interrupt_count == 3){	    /*Every 5 ms we increment the variable. If its the third time, we set OCR1A*/
		OCR1A = converted_valueA;   /*Refresh the OCR1A/B values to generate a new PWM signal*/
		OCR1B = converted_valueB;
		interrupt_count = -1;	    /*So that when Timer1 starts counting again from 0, the value of interrupt_count is 0 and Timer1 and Timer0 stay synchronised*/
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------
This timer is used to syncronize the actualization of the OCR1A/B registers, every 3 interrupts from this counter, we will modify the OCR1A (every 15 ms, (one interrupt each 5 ms) and then generate the next PWM signal after 5 ms more (20 ms).
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void PWM_Timer0_Init(){
  PRR &= ~(1<<PRTIM0);                                       /*Activate  Timer0*/
  TCCR0A |=(1<<WGM01);                                       /*Configure Timer mode CTC*/
  TIMSK0 |= (1<<OCIE0A);				     /*Unmask Compare Match interrupt with OCR0A register*/
  TIFR0 |= (1<< OCF0A);					     /*Clear interrupt flag just in case*/
  TCNT0 = 0x00;	
  OCR0A = 78; 						     /*So that each Match takes 5 ms*/
}

void PWM_Timer0_Start(){
  TCCR0B = TCCR0B | (1 << CS02) | (1 << CS00); 		   /*Prescaler set to f/1024 = 15625 Hz*/
}
