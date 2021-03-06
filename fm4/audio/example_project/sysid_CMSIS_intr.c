// sysid_CMSIS_intr.c

#include "audio.h"

volatile int16_t audio_chR=0;    
volatile int16_t audio_chL=0;    

#define BLOCK_SIZE 1
#define NUM_TAPS 256

float32_t beta = 1E-12;
float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
float32_t firCoeffs32[NUM_TAPS] = { 0.0f };
arm_lms_instance_f32 S;
float32_t yn, adapt_in, adapt_out, adapt_err,input,wn;


void I2S_HANDLER(void) { 
	
int16_t audio_out_chL = 0;
int16_t audio_out_chR = 0;
	
audio_IN = i2s_rx();	
audio_chL = (audio_IN & 0x0000FFFF);       
audio_chR = ((audio_IN >>16)& 0x0000FFFF); 

	    input = (float32_t)(audio_chL);
		  adapt_in = (float32_t)(prbs());
      audio_out_chL = (int16_t)(adapt_in);
	    audio_out_chR = 0;
audio_OUT = ((audio_out_chR<<16 & 0xFFFF0000)) + (audio_out_chL & 0x0000FFFF);	
i2s_tx(audio_OUT);		
      gpio_set(P2_10, HIGH);
		  arm_lms_f32(&S, &adapt_in, &input, &adapt_out, &adapt_err, BLOCK_SIZE);	
      gpio_set(P2_10, LOW);
}

int main(void) 
{
	gpio_set_mode(P2_10, Output);
	arm_lms_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], beta, BLOCK_SIZE);
  audio_init ( hz8000, line_in, intr, I2S_HANDLER); 

  while(1){}
}

