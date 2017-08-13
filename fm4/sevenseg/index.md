# Using a Seven Segment Display

As part of a project I want to output some letters/numbers on a 7 Segment Display. I just so happen to have one of these laying around so thought I'd give it a go! 

<img src="http://haneefputtur.com/wp-content/uploads/2016/02/pic7segment.jpg">

It also happens that there is an arduino guide for it [here](http://haneefputtur.com/7-segment-4-digit-led-display-sma420564-using-arduino.html)

## First Steps

![schematic](schematic.PNG)

The first thing I did was to plug the segment controls into CN7 pins on the dev kit. I also grounded the `d1` cathode. This means that when I set the relevant pins of the FM4 to be `HIGH` output all of the bits of the display will turn on. 

``` c
int main(void)
{
	// All segments on
	Gpio1pin_InitOut(GPIO1PIN_P16, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P42, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P40, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P41, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_PF0, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_PF1, Gpio1pin_InitVal(1u));
	Gpio1pin_InitOut(GPIO1PIN_P7D, Gpio1pin_InitVal(1u));
	   
    while(1)
    {
    }
}
```

And my output:

![output](all_on.JPG)

# Controlling It
With the 7 segement display I want to make somethings appear, `1`, `2`, `3`, ... and so on. And to make a segment turn on, using my __common cathode__ display I need to make the input to it `HIGH`. To make a 1 appear I need to have segments `b` and `c` on, and the rest off, for example. I made a table to help me with this:

| Segment | Pin | Port/Pin | Display `1` | Display `2` | Display `3` |Display `4` |Display `5` |Display `6` |Display `7` |Display `8` |Display `9` |Display `0` |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| a | 55| 7D | LOW  | HIGH |HIGH |LOW |  HIGH |HIGH |HIGH |HIGH |HIGH |HIGH |
| b | 64| F1 | HIGH | HIGH |HIGH |HIGH | LOW  |LOW  |HIGH |HIGH |HIGH |HIGH |
| c | 63| F0 | HIGH | LOW  |HIGH |HIGH | HIGH |HIGH |HIGH |HIGH |HIGH |HIGH |
| d | 47| 41 |  LOW |  HIGH| HIGH| LOW|   HIGH| HIGH| LOW |HIGH |HIGH |HIGH |
| e | 46| 40 |  LOW |  HIGH| LOW | LOW |  LOW | HIGH| LOW |HIGH |LOW  |HIGH |
| f | 42| 42 | LOW  | LOW  |LOW  |HIGH  | HIGH| HIGH|LOW  |HIGH |HIGH |HIGH |
| g | 100| 16| LOW  | HIGH |HIGH |HIGH | HIGH |HIGH |LOW  |HIGH |HIGH |LOW  |

To practice this I setup the [Dual Timer](../timer/index.md) to generate an interrupt, in this interrupt I change the digit shown. Here's an example of how a digit is shown:

``` c
void show_six( void ){
	Gpio1pin_Put( GPIO1PIN_P7D, 1u );
	Gpio1pin_Put( GPIO1PIN_PF1, 0u );
	Gpio1pin_Put( GPIO1PIN_PF0, 1u );
	Gpio1pin_Put( GPIO1PIN_P41, 1u );
	Gpio1pin_Put( GPIO1PIN_P40, 1u );
	Gpio1pin_Put( GPIO1PIN_P42, 1u );
	Gpio1pin_Put( GPIO1PIN_P16, 1u );
}
```

And here's how the Timer interrupt makes the change:

```c
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
```

The full code can be found [here](count_loop.c)

And this is the output:

![output](sevenseg_loop.gif)

This means I can successfully use the Dual Timer and the 7 segment display. Though it's not that easy to used cause there's lots of repeatition in the code and in setting the digits up.

## Improvements

One way to improve the code is to reduce the number of `Gpio1pin_Put` uses and instead use portwise instructions instead. So lets find a port which can be used!

![pins](port1_pins.png)

It just so happens that Port 1 has 8 pins exposed via the FM4's spare pins so lets use Port1