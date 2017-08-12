/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "mcu.h"
#include "gpio.h"
#include "dt.h"

#define COUNTS_FOR_1_S                                                156250u
#define COUNTS_FOR_500_MS                                              78125u


void show_one( void );
void show_two( void );
void show_three( void );
void show_four( void );
void show_five( void );
void show_six( void );
void show_seven( void );
void show_eight( void );
void show_nine( void );
void show_zero( void ); 
void configure_gpio( void );
void configure_timer( void );

void DT_IRQHandler(void){
	  static int timer_count = 0;
    Dt_ClrIrqFlag(DtChannel0);    /* Clear Irq */
		switch(timer_count){
			case 0: show_one(); timer_count++;   break;
			case 1: show_two(); timer_count = 0; break;
			default: timer_count = 0; break;
		}	
}

int main(void)
{
  configure_gpio();
	configure_timer();
	Gpio1pin_Put(GPIO1PIN_P1A,  1u);
	show_two();

  while(1);
}

void configure_gpio( void ){
		// All segments on
  Gpio1pin_InitOut(GPIO1PIN_P7D, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_PF1, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_PF0, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P41, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P40, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P42, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P16, Gpio1pin_InitVal(1u));
	
	// Red RGB
	Gpio1pin_InitOut(GPIO1PIN_P1A,  Gpio1pin_InitVal(0u));
}

void show_one( void ){
	Gpio1pin_Put( GPIO1PIN_P7D,0u );
	Gpio1pin_Put( GPIO1PIN_PF1,1u );
	Gpio1pin_Put( GPIO1PIN_PF0,1u );
	Gpio1pin_Put( GPIO1PIN_P41,0u );
	Gpio1pin_Put( GPIO1PIN_P40,0u );
	Gpio1pin_Put( GPIO1PIN_P42,0u );
	Gpio1pin_Put( GPIO1PIN_P16,0u );
}

void show_two( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
	Gpio1pin_Put( GPIO1PIN_PF0, 0u );
	Gpio1pin_Put( GPIO1PIN_P41, 1u );
	Gpio1pin_Put( GPIO1PIN_P40, 1u );
	Gpio1pin_Put( GPIO1PIN_P42, 0u );
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
}


void show_eight( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
  Gpio1pin_Put( GPIO1PIN_PF0, 1u );
  Gpio1pin_Put( GPIO1PIN_P41, 1u );
  Gpio1pin_Put( GPIO1PIN_P40, 1u ); 
  Gpio1pin_Put( GPIO1PIN_P42, 1u );
  Gpio1pin_Put( GPIO1PIN_P16, 1u );
}
void configure_timer( void ){
	stc_dt_channel_config_t stcDtChannelConfig0;
  
	  stcDtChannelConfig0.u8Mode = DtPeriodic;
    stcDtChannelConfig0.u8PrescalerDiv = DtPrescalerDiv256;
    stcDtChannelConfig0.u8CounterSize = DtCounterSize32; 
    stcDtChannelConfig0.bIrqEnable = TRUE;
    stcDtChannelConfig0.pfnIrqCallback = DT_IRQHandler;
    stcDtChannelConfig0.bTouchNvic = TRUE;
	
    /* Initialize dual timer channel 0 */
    if (Ok != Dt_Init((stc_dt_channel_config_t*)&stcDtChannelConfig0, DtChannel0))
    {
			Gpio1pin_Put(GPIO1PIN_P1A, 1u);
        while(1);
    }

    /* Write load value for channel 0 (0.5sec interval @ PCLK = 80MHz) */
    Dt_WriteLoadVal(COUNTS_FOR_1_MS, DtChannel0);
    /* Write background load value for channel 0 (0.5sec -> 1sec @ PCLK = 80MHz) */
    Dt_WriteBgLoadVal(COUNTS_FOR_1_S, DtChannel0);
    /* Start count for channel 0 */
    Dt_EnableCount(DtChannel0);
	
}
