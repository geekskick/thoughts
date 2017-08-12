#Using a Seven Segment Display

As part of a project I want to output some letters/numbers on a 7 Segment Display. I just so happen to have one of these laying around so thought I'd give it a go! 

<img src="http://haneefputtur.com/wp-content/uploads/2016/02/pic7segment.jpg">

It also happens that there is an arduino guide for it [here](http://haneefputtur.com/7-segment-4-digit-led-display-sma420564-using-arduino.html)

## First Steps
<img src="schematic.png">
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
<img src="all_on.jpg">

#Controlling It
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