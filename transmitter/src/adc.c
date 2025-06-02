
#include "common.h"
#include <avr/interrupt.h>

/*We declare the variables outside the functions so that they can be accessed from the main file*/

volatile int8_t channel = 0;		
volatile uint8_t obtainedData;
volatile int8_t sendData = 0;
volatile int8_t lastChannel;

/*------------------------------------------------------------------------------------------------*/
/*ISR that executes when a Counter Match with Timer1 occurs, we start immediately a new conversion*/
/*------------------------------------------------------------------------------------------------*/

ISR(TIMER1_COMPB_vect){} /*We clear the interrup flag so that more conversions can be made, if I don't do that, the ADC won't work properly*/
  
/*-------------------------------------------------------------------*/
/*ISR that executes when the converted data from the ADC is available*/
/*-------------------------------------------------------------------*/

ISR(ADC_vect){
  obtainedData =  ADCH;  /*Obtain the converted data from the conversion*/
  sendData = 1;          /*Set to 1 so that the main thread procceeds*/
  lastChannel = channel; /*We save the actual channel we converted*/
  
  if(++channel >= NUM_ELEMENTS) channel = 0;   /*Once we converted the second channel, we start from the first one again*/ 
  ADMUX = (ADMUX & ~ADMUX_MUX) | channel;      /*Set the next channel to be converted*/
}

/*----------------------------------------
Function that initialices the ADC features
----------------------------------------*/

void ADC_Init(){
    PRR &= ~(1<<PRADC);                                                          /*Deactivate PRADC from PRR in case it was activated*/
    ADCSRA |=(1<< ADEN);                                                         /*Activate the ADC*/
    ADCSRA |= (1<<ADIE);                                                         /*Activate ADC interrupt when conversion completed*/ 
    ADCSRA = ADCSRA |((1<< ADPS2)|((1<<ADPS1) &~(1<<ADPS0)));                    /*Configure ADC prescaler to obtain a 250 kHz work frequency.*/
    DDRC = DDRC & (~(1 << pinX1) & ~(1<< pinY1) & ~(1<< pinX2) & ~(1 << pinY2)); /*Configure joysticks pins as inputs*/
    ADMUX = ADMUX |((1<< REFS0) &~(1<<REFS1));                                   /*Configure voltage reference to Vcc*/
    ADMUX |= (1<< ADLAR);                                                        /*Activate ADLAR, 8 bit conversion precision*/
    ADCSRB = ADCSRB  |  ((1<<ADTS2) | (1<<ADTS0));                               /*Configure ADC Trigger Source as Timer/Counter1 Compare Match B*/
    ADCSRA |= (1<<ADATE);                                                        /*Activate the auto-trigger*/
    ADMUX = (ADMUX & ~ADMUX_MUX) | channel;			                 /*First channel to be converted will be 0*/   
    /*Once the auto-trigger is activated, the conversions will start at the first Trigger Source pulse*/
}
/*----------------------------------------------------------------------------------------------
Function that initializes Timer1 to serve as the trigger source for the ADC auto-trigger feature
----------------------------------------------------------------------------------------------*/

void Autotrigger_Init(){ 
   PRR &= ~(1<<PRTIM1);        		          /*Activate Timer1*/
   TCNT1 = 0x00;               			  /*We reset the value of the Counter in case it wasn't initially 0. */
   TIMSK1 |= (1 << OCIE1B);    			  /*Unmask the interruptions of Compare Match B */
   TCCR1B = TCCR1B | (1<< WGM12) | (1<<WGM13);    /*Configure Timer mode CTC where TOP is ICR1*/ 	 
   ICR1 = AUTO_TRIGGER_PERIOD;  		  /*Set the Compare Value, the value is calculated so that it takes around 3 ms to do a Match*/
   OCR1B = ICR1;              		  	  /*So that when we reach the TOP, the interrupt is executed */
   TIFR1 |= (1 << OCF1B);	   		  /*Clear interrupt flag just in case*/		 	
}
/*--------------------------------------
Function that starts the ADC conversions 
--------------------------------------*/

void start_ADC_conversion(){
  TCCR1B |= (1<<CS11);              /*Adjust the preescaler to work with f = 2 MHz. This starts the counter*/ 
}


