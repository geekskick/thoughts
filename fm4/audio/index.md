# Audio on the FM4

According to the FM4 datasheet the headphone jack on the dev kit is connected to an Audio Codec. It's the codec's job to turn sounds (analogue signals) into data for the S6E2CC core, and vice versa. The codec on the dev kit is a WM8731, manufactured by Wolfson.

<img src="codec_sch.png">

## Example Project

I have used the reference project provided by ARM University and used this as a starting point to see what they do. This can be found in [here](example_project).

The project's main basically does the following things:
1. Setup the audio codec
2. Nothing

It seems abit too simple to me so I thought I'd investigate it to understand what's happening. 

## Set Up the Audio Codec
The [main](example_project/fir_intr.c) calls the function `audio_init` which is implemented in [audio.c](example_project/audio.c). The first thing this does is to initialese the I2C, why does it do this? 

Well if we examine the datasheet codec it tells us in the *Software Control Interface* section that this is achievied using the SDIN pin. Also, on the schematic we notice that the MODE and CSB pins are grounded on the development kit.

<img src="codec_mode_pins.png">

And in the datasheet for the codec is says that those pins correspond to how the control registers are written to, I2C vs SPI and it's address.

<img src="codec_mode_tbl.png">
So we are using I2C.
<img src="codec_csb_tbl.png">
at address `0x1A`.

### I2C Initialise
The example project doesn't use the PDL, so it manipulates the registers directly - I suppose this prevents a bloated codebase?

With any microcontroller the first thing I would expect to happen in an intialisation routine is for the pins to be correctly set up - In/Out/PullUp/PullDown ...

On the FM4 dev kit the control register pins are labelled as SOT2_1 and SCK2_1 (pins 36 and 36)

<img src="rc_pins_codec.png">

which on the MCU are associated with Port 3 pins A and B

<img src="mcu_rc_pins.png">

According to the FM4 peripheral datasheet the **PFR** register determines whether the pin is being used as GPIO or by a peripheral,

<img src="pfrx.png">

so I would expect that those 2 pins at some point would have a value of 1 written to the the PFR3 register in the relevant bits.

<img src="pfr3_offset.png">

and viola! It does this by using the macro `bFM4_GPIOPRF3_PA = 1u`. *Using what I learned about the bit Band Aliasing (and my [nifty converter](bbaregion.c])) I expect this to translate to `0x42de01a8`, and confirming it using `s6e2ccxj.h` line 69898 it says `#define bFM4_GPIO_PFR3_PA *((volatile  uint8_t *)(0x42DE01A8UL))`*

Then it enables the pin on the peripheral side by using the **E**xtended **P**eripheral **F**unction **R**egister. A quick `ctrl-f` for the function `SOT2_1` quickly finds in the document the EPFR Settings Register 07. This tells me that Bits 19 and 18 need to be set to `b10` to use `SOT2_1`. So the bit 19 needs to be `1` and 18 needs to be `0`.

### Resources
* [Codec Datasheet](https://www.rockbox.org/wiki/pub/Main/DataSheets/WM8731_8731L.pdf)