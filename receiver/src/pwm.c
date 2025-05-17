#include "common.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------
This function configures the require settings to generate PWM signals. We will use the Timer1 (16 bit). We will set the PWM frequency, mode of   
operation and the OC1A and OC1B output pin modes.                                                                                            
---------------------------------------------------------------------------------------------------------------------------------------------------*/

void PWM_Init(){

  PRR &= ~(1<<PRTIM1);        			   	   /*Activate Timer1*/
  DDRB |= (1<<DD_OC1A) | (1<<DD_OC1B);     		   /*Configure pins OC1A (PB1) and OC1B (PB2) as OUTPUTS*/
  TCNT1 = 0x00;               			           /*We reset the value of the Counter in case it wasn't initially 0. */
  TCCR1B |= (1 << WGM13) | (1 << WGM12); 		   /*We set Fast-PWM mode, perfect for controlling servomotors*/
  
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);/*OC1A/B bits will be cleared when matching (OCR1A) upcounting and set when reaching bottom*/
  ICR1 = PWM_PERIOD;  	    			 /*This sets the TOP value to 625*/
  OCR1A = IDLE_STATE;                            /*Initially, the servomotors won't move, that's equal to set the OCR1A/B to that value*/
  OCR1B = IDLE_STATE;
}

/*--------------------------------------------
Function that starts the counting from Timer1.
--------------------------------------------*/

void PWM_Start(){
   TCCR1B |=(1 << CS12); /*Configure prescaler to f/256 = 62500 Hz. This starts the counting*/
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
Function that obtains the converted values for the Timer1 OCR1A and OCR1B depending on the digitally converted joystick value. Linear interpolation is used to convert digital ADC value into OCR1A value (OCR1A value sets the PWM pulse widht, that directly controls the speed of the servomotor). 
´                             
Parameters:
		ejeX: Digitally converted value of the joystick X axis value
		ejeY: Digitally converted value of the joystick Y axis value
		*converted_valueA: Pointer to the variable where we save the last converted value obtained from X axis
		*converted_valueB: Pointer to the variable where we save the last converted value obtained from Y axis
		
---------------------------------------------------------------------------------------------------------------------------------------------------*/

void Convert_Value_PWM(uint8_t ejeX,uint8_t ejeY,volatile int16_t *converted_valueA,volatile int16_t *converted_valueB){	
	
   *converted_valueA = (12500 - 25*ejeX)/100;
   *converted_valueB = (12500 - 25*ejeY)/100;
	
}
	    

