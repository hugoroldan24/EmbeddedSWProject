/*
 * Wireless Dual-Servo Controller
 * (c) 2025 Hugo Roldán López
 * This file is part of the project licensed under the MIT License.
 * See the LICENSE file in the root of the repository for full license text.
 */
 
 
 /***********************************************************************************************************
 * main.c
 *
 * Brief Description:
 * Entry point for the wireless dual-servo transmitter. Initializes all required peripherals
 * (SPI, ADC auto-trigger, ADC, and nRF24L01+ as transmitter) and enters a loop that waits
 * for ADC conversions to complete. Once both joystick channels are sampled, it packages the
 * data and sends it via RF.
 *
 * Workflow:
 *   1. transmitter_config() initialice ADC, ADC Auto-trigger, SPI, RF module as TX and starts the conversions
 *   2. Timer1 triggers ADC conversions; each completed conversion sets sendData flag.
 *   3. ISR(ADC_vect) stores the new ADC sample in obtainedData and records lastChannel.
 *   4. In main loop, once both channels are read (lastChannel == NUM_ELEMENTS-1), call
 *      sendPaquet() to transmit the data packet via nRF24L01+.
 *
 ************************************************************************************************************/
 
 
#include "common.h"
#include "transmitter.h"
#include "radio.h"


extern volatile int8_t obtainedData; /* Variable where we save the converted data */
extern volatile int8_t sendData;     /* Conversion completed flag */
extern volatile int8_t lastChannel;  /* Last channel that was converted */


/**
 * @brief  Main function for the transmitter firmware.
 *         Initializes all transmitter-side peripherals and enters an infinite loop that:
 *           - Waits for ADC conversion to complete (sendData flag).
 *           - Stores the obtained sample in the data packet array at index lastChannel.
 *           - When both joystick channels are sampled (lastChannel == NUM_ELEMENTS-1),
 *             calls sendPaquet() to send the full packet via the RF module.
 * @return int  Always returns 0 (never reached in embedded).
 */
int main(void)
{
  uint8_t data_paquet[NUM_ELEMENTS];
  transmitter_config();	   	    /*Initialices all the transmitter features*/
  
  while(1){				       
     while(!sendData);              /* Wait until an ADC conversion is complete */
     sendData = 0;  
     data_paquet[lastChannel] = obtainedData;
    
     if(lastChannel == NUM_ELEMENTS-1) sendPaquet(data_paquet,NUM_ELEMENTS); /* Transmit the packet once both channels are read */
  }  
  
  return 0;
}

