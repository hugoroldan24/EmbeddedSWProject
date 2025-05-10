#include "common.h"

/*-------------------------------------------------------------------------
Function that gives a us delay between 1 and 127 us. It uses the Timer0

Parameter:
		time: Delay time required.
-------------------------------------------------------------------------*/
void delay_us(int8_t time){

  TCNT0 = 0x0;                                              /* We set the Counting Register to 0 */
  OCR0A = 2 * time;                                         /* 2 cicles/us * time(us) = num cicles */
  TCCR0B |= (1<<CS01);                                      /*Adjust the preescaler to work with f = 2 MHz. This starts the counter*/
  while(!READ_BIT(TIFR0,OCF0A));                            /*Polling the bit OCF0A in TIFR0, (1 means that a Counter Match occurred*/ 
  TIFR0 |= (1<<OCF0A);                                      /* Clean the bit OCF0A in TIFR0 */
  TCCR0B = TCCR0B & (~(1<<CS02) & ~(1<<CS01) & ~(1<<CS00)); /* No prescaler, timer is stopped */
}

/*--------------------------------------
Function that initialices the Timer0
--------------------------------------*/

void init_delay_timer(){

  PRR &= ~(1<<PRTIM0);                                      /*Activate  Timer0*/
  TCCR0A |=(1<< WGM01);                                     /*Configure Timer mode CTC*/
  TCCR0B = TCCR0B & (~(1<<CS02) & ~(1<<CS01) & ~(1<<CS00)); /* No prescaler, timer is stopped */
	
}
