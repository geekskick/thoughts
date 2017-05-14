// fir_intr.c 

#include "audio.h"

volatile int16_t audio_chR=0;    
volatile int16_t audio_chL=0;    

#include "lpf.h"
#include "fdacoefs_bp.h"
#include "fdacoefs_hp.h"

#define LP_GAIN 1
#define BP_GAIN 0.5
#define HP_GAIN 1

extern const float32_t lpf_h[N];
extern const float32_t bpf_h[N];
extern const float32_t hpf_h[N];

float32_t x[N];
int16_t k = 0;

float32_t convolute( const float32_t *pCoefficients, const float32_t gain )
{
	 float32_t rc = 0.0;
	 int i;
    if (k >= N) k = 0;
    for (i=0 ; i<N ; i++)
    {
      rc += pCoefficients[i] * x[k++] * gain;
			if (k >= N) k = 0;
		}
 	  return rc;
}


void I2S_HANDLER(void) {                  

audio_IN = i2s_rx();	
audio_chL = (audio_IN & 0x0000FFFF);       
audio_chR = ((audio_IN >>16)& 0x0000FFFF); 

    x[k++] = (float32_t)audio_chL;
	//audio_chL = (int16_t)convolute( hpf_h, HP_GAIN );
	audio_chL = (int16_t)convolute( bpf_h, BP_GAIN ) + (int16_t)convolute( lpf_h, LP_GAIN ) + (int16_t)convolute( hpf_h, HP_GAIN );
		
audio_OUT = ((audio_chL <<16 & 0xFFFF0000)) + (audio_chL & 0x0000FFFF);	
i2s_tx(audio_OUT);

}

int main(void)
{

  audio_init ( hz48000, line_in, intr, I2S_HANDLER); 
  while(1){}
}
