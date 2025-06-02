#include "common.h"
#include <avr/interrupt.h>


extern volatile uint16_t servo_A;
extern volatile uint16_t servo_B;
volatile int8_t interrupt_count = 0;

/*----------------------------------------------------------
ISR that is executed when the Timer0 reaches the OCR0A value. 
----------------------------------------------------------*/

ISR(TIMER0_COMPA_vect){
	if(++interrupt_count == 3){	    /*Every 5 ms we increment the variable. If its the third time, we set OCR1A*/
		OCR1A = servo_A;  	    /*Refresh the OCR1A/B values to generate a new PWM signal*/
		OCR1B = servo_B;
		interrupt_count = -1;	    /*So that when Timer1 starts counting again from 0, the value of interrupt_count is 0 and Timer1 and Timer0 stay synchronised*/
	}
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
This function configures the required settings to generate PWM signals. We will use the Timer1 (16 bit). We will set the PWM frequency, mode of   
operation and the OC1A and OC1B output pin modes.                                                                                            
---------------------------------------------------------------------------------------------------------------------------------------------------*/

void PWM_Init(){
  PRR &= ~(1<<PRTIM1);        			   	   /*Activate Timer1*/
  DDRB |= (1<<DD_OC1A) | (1<<DD_OC1B);     		   /*Configure pins OC1A (PB1) and OC1B (PB2) as OUTPUTS*/
  TCNT1 = 0x00;               			           /*We reset the value of the Counter in case it wasn't initially 0. */
  TCCR1B |= (1 << WGM13) | (1 << WGM12); 		   /*We set Fast-PWM mode, perfect for controlling servomotors*/
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);  /*OC1A/B bits will be cleared when matching (OCR1A) upcounting and set when reaching bottom*/
  ICR1 = PWM_PERIOD;  	    			 	   /*This sets the TOP value to pwm_period*/
  OCR1A = IDLE_STATE;                            	   /*Initially, the servomotors won't move, that's equal to set the OCR1A/B to that value*/
  OCR1B = IDLE_STATE;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------
This timer is used to syncronize the actualization of the OCR1A/B registers, every 3 interrupts from this counter, we will modify the OCR1A (every 15 ms, (one interrupt each 5 ms) and then generate the next PWM signal after 5 ms more (20 ms). 
I used this functionality basically because since the servomotor can only receive new input every 20 ms (50 Hz), I didn't want to refresh the OCR1A/B register multiple times (in 20 ms we receive a lot of new paquets but we can only procces 1) and only once every 15 ms.
---------------------------------------------------------------------------------------------------------------------------------------------------*/

void PWM_Timer0_Init(){

  PRR &= ~(1<<PRTIM0);                                       /*Activate  Timer0*/
  TCCR0A |=(1<<WGM01);                                       /*Configure Timer mode CTC*/
  TIMSK0 |= (1<<OCIE0A);				     /*Unmask Compare Match interrupt with OCR0A register*/
  TIFR0 |= (1<< OCF0A);					     /*Clear interrupt flag just in case*/
  TCNT0 = 0x00;	
  OCR0A = TIMER0_PERIOD;         		     /*So that each Match takes 5 ms*/ 
}


/*--------------------------------------------
Function that starts the counting from Timer1.
--------------------------------------------*/

void PWM_Start(){
   TCCR1B |=(1 << CS12); 					   /*Configure prescaler to f/256 = 62500 Hz. This starts to generate PWM signals*/
   TCCR0B = TCCR0B | (1 << CS02) | (1 << CS00); 		   /*Prescaler set to f/1024 = 15625 Hz*/. This starts the synchronisation Timer*/  
}

	
/*---------------------------------------------------------------------------------------------------------------------------------------------------
Function that applies linear interpolation to map joystick values (0–255) to a value suitable for the OCR1A/B registers, which define the PWM signal's pulse width.
´                             
Parameters:
		Xaxis: Digitally converted value of the joystick X axis value
		Yaxis: Digitally converted value of the joystick Y axis value
		*converted_valueA: Pointer to the variable where we save the last converted value obtained from X axis
		*converted_valueB: Pointer to the variable where we save the last converted value obtained from Y axis
		
---------------------------------------------------------------------------------------------------------------------------------------------------*/

void Convert_Value_PWM(uint8_t Xaxis,uint8_t Yaxis,volatile int16_t *converted_valueA,volatile int16_t *converted_valueB){		
   *converted_valueA = (a + b*Xaxis)/100;
   *converted_valueB = (a + b*Yaxis)/100;	
}

    

