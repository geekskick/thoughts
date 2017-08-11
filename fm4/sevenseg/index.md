#Using a Seven Segment Display

As part of a project I want to output some letters/numbers on a 7 Segment Display. I just so happen to have one of these laying around so thought I'd give it a go! 

<img src="http://haneefputtur.com/wp-content/uploads/2016/02/pic7segment.jpg">

It also happens that there is an arduino guide for it [here](http://haneefputtur.com/7-segment-4-digit-led-display-sma420564-using-arduino.html)

## First Steps
<img src="schematic.png">
The first thing I did was to plug the segment controls into CN7 pins on the dev kit. I also grounded the `d1` cathode. This means that when I set the relevant pins of the FM4 to be `HIGH` output all of the bits of the display will turn on. 