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

which on the MCU are associated with Port 3 pins A and B.

<img src="mcu_rc_pins.png">

### Resources
* [Codec Datasheet](https://www.rockbox.org/wiki/pub/Main/DataSheets/WM8731_8731L.pdf)