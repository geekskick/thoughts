# Audio on the FM4

> In this bit code snippets in these quote blocks are taken from the [example project](example_project).

According to the FM4 datasheet the headphone jack on the dev kit is connected to an Audio Codec. It's the codec's job to turn sounds (analogue signals) into data for the S6E2CC core, and vice versa. The codec on the dev kit is a WM8731, manufactured by Wolfson.

<img src="codec_sch.png">

## Example Project

I have used the reference project provided by ARM University and used this as a starting point to see what they do. This can be found in [here](example_project).

The project's main basically does the following things:
1. Setup the audio codec
2. Nothing

It seems abit too simple to me so I thought I'd investigate it to understand what's happening. 

what I didn't say was that the [main](example_project/fir_intr.c) calls the function `audio_init` which is implemented in [audio.c](example_project/audio.c). The first thing this does is to initialise the I2C, why does it do this? 

## Connections to the Codec

Well if we examine the datasheet codec it tells us in the *Software Control Interface* section that this is achievied using the SDIN pin. Also, on the schematic we notice that the MODE and CSB pins are grounded on the development kit.

<img src="codec_mode_pins.png">

And in the datasheet for the codec is says that those pins correspond to how the control registers are written to, I2C vs SPI and it's address.

<img src="codec_mode_tbl.png">

So we are using I2C.

<img src="codec_csb_tbl.png">

at address `0x1A`

### I2C Initialise
[The I2C Interface is setup](MFS-I2C_Setup.md) to control the codec.

### Codec Settings
The MFS peripheral is used to perform the [codec settings and I2S communications](codec_setup.md)

### I2S FM4 Peripheral Setup
[The I2S Peripheral Setup is detailed here](i2S_Peripheral_Setup.md)