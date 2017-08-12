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

static uint32_t timer_count;

static void DtCallback(void){
    Dt_ClrIrqFlag(DtChannel0);    /* Clear Irq */
		switch(timer_count){
			case 0: show_one(); timer_count++;   break;
			case 1: show_two(); timer_count = 0; break;
			default: timer_count = 0; break;
		}
		
}

void start_timer( const uint32_t value ){
 /* Write load value for channel  */
  Dt_WriteLoadVal(value, DtChannel0);
  /* Start count for channel 0 */
  Dt_EnableCount(DtChannel0);
}

void configure_timer( void ){
	stc_dt_channel_config_t stcDtChannelConfig0;
  
	timer_count = 0;
  
  /* Initialize configuration */
  stcDtChannelConfig0.u8Mode = DtPeriodic;
  stcDtChannelConfig0.u8PrescalerDiv = DtPrescalerDiv256;
  stcDtChannelConfig0.u8CounterSize = DtCounterSize32; 
  stcDtChannelConfig0.bIrqEnable = TRUE;
  stcDtChannelConfig0.pfnIrqCallback = DtCallback;
  stcDtChannelConfig0.bTouchNvic = TRUE;
	Dt_WriteBgLoadVal(COUNTS_FOR_1_S, DtChannel0);
	Dt_WriteLoadVal(COUNTS_FOR_1_S, DtChannel0);
	Dt_Init( &stcDtChannelConfig0, DtChannel0 );
}

void configure_gpio( void ){
		// All segments on
  Gpio1pin_InitOut(GPIO1PIN_P16, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P42, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P40, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P41, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_PF0, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_PF1, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P7D, Gpio1pin_InitVal(1u));
}

int main(void)
{
  configure_gpio();
	configure_timer();
	start_timer( COUNTS_FOR_1_S );
	  
    while(1)
    {

    }
}

void show_one( void ){
	Gpio1pin_Put(GPIO1PIN_P16,0u );
	Gpio1pin_Put(GPIO1PIN_P42,1u );
	Gpio1pin_Put(GPIO1PIN_P40,1u );
	Gpio1pin_Put(GPIO1PIN_P41,0u );
	Gpio1pin_Put(GPIO1PIN_PF0,0u );
	Gpio1pin_Put(GPIO1PIN_PF1,0u );
	Gpio1pin_Put(GPIO1PIN_P7D,0u );
}

void show_two( void ){
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
	Gpio1pin_Put( GPIO1PIN_P42, 1u );
	Gpio1pin_Put( GPIO1PIN_P40, 0u );
	Gpio1pin_Put( GPIO1PIN_P41, 1u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 0u );
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
}


/* [] END OF FILE */
