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

/* 
TimerVal = Interval * (TIMCLKfreq/Prescale) - 1
therefore with a PRESCALE @ 256, and a TIMCLK set by the APB Clock at 100MHz
Interval = 1sec, therefore 1 * (100*10^6) - 1 = 390625 - 1 = 390624
Interval = 0.5sec, therefore 0.5 * (100*10^6) - 1 = (390625/2) - 1 = 195313 - 1 = 195312
*/
#define COUNTS_FOR_1_S                                                390624u
#define COUNTS_FOR_500_MS                                             195312u

#define Seg_Zero  0x3F
#define Seg_One   0x06
#define Seg_Two   0x5B
#define Seg_Three 0x4F
#define Seg_Four  0x66
#define Seg_Five  0x6D
#define Seg_Six	  0x7D
#define Seg_Seven 0x07
#define Seg_Eight 0x7F
#define Seg_Nine  0x6F

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
			case 0: show_zero(); timer_count++; break;
			case 1: show_one(); timer_count++; break;
			case 2: show_two(); timer_count++; break;
			case 3: show_three(); timer_count++; break;
			case 4: show_four(); timer_count++; break;
			case 5: show_five(); timer_count++; break;
			case 6: show_six(); timer_count++; break;
			case 7: show_seven(); timer_count++; break;
			case 8: show_eight(); timer_count++; break;
			case 9: show_nine(); timer_count = 0; break;
			default: timer_count = 0; break;
		}	
}

int main(void)
{
  configure_gpio();
	//configure_timer();
	show_one();
	Gpio1pin_Put(GPIO1PIN_P1A,  1u);

  while(1);
}

void configure_gpio( void ){
		// All segments on
  Gpio1pin_InitOut(GPIO1PIN_P10, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P11, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P12, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P13, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P14, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P15, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P16, Gpio1pin_InitVal(1u));
	
	// Red RGB
	Gpio1pin_InitOut(GPIO1PIN_P1A,  Gpio1pin_InitVal(0u));
}

void show_one( void ){
	FM4_GPIO_PDOR1 = Seg_One;
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

void show_three( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_P41, 1u );
	Gpio1pin_Put( GPIO1PIN_P40, 0u );
	Gpio1pin_Put( GPIO1PIN_P42, 0u );
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
}

void show_four( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 0u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_P41, 0u );
	Gpio1pin_Put( GPIO1PIN_P40, 0u );
	Gpio1pin_Put( GPIO1PIN_P42, 1u );
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
}

void show_five( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 0u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_P41, 1u );
	Gpio1pin_Put( GPIO1PIN_P40, 0u );
	Gpio1pin_Put( GPIO1PIN_P42, 1u );
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
}

void show_six( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 0u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_P41, 1u );
	Gpio1pin_Put( GPIO1PIN_P40, 1u );
	Gpio1pin_Put( GPIO1PIN_P42, 1u );
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
}

void show_seven( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_P41, 0u );
	Gpio1pin_Put( GPIO1PIN_P40, 0u );
	Gpio1pin_Put( GPIO1PIN_P42, 0u );
	Gpio1pin_Put( GPIO1PIN_P16, 0u );
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

void show_nine( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
  Gpio1pin_Put( GPIO1PIN_PF0, 1u );
  Gpio1pin_Put( GPIO1PIN_P41, 1u );
  Gpio1pin_Put( GPIO1PIN_P40, 0u ); 
  Gpio1pin_Put( GPIO1PIN_P42, 1u );
  Gpio1pin_Put( GPIO1PIN_P16, 1u );
}

void show_zero( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 1u );
  Gpio1pin_Put( GPIO1PIN_PF0, 1u );
  Gpio1pin_Put( GPIO1PIN_P41, 1u );
  Gpio1pin_Put( GPIO1PIN_P40, 1u ); 
  Gpio1pin_Put( GPIO1PIN_P42, 1u );
  Gpio1pin_Put( GPIO1PIN_P16, 0u );
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

  /* Write load value for channel 0 (1sec interval @ PCLK = 100MHz) */
  Dt_WriteLoadVal(COUNTS_FOR_500_MS, DtChannel0);
  /* Write background load value for channel 0 (1sec @ PCLK = 100MHz) */
  Dt_WriteBgLoadVal(COUNTS_FOR_500_MS, DtChannel0);
  /* Start count for channel 0 */
  Dt_EnableCount(DtChannel0);
}
