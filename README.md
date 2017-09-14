# Datalogger
The program read the message from the Serial, show the message on the LCD screen and finally save the message into the SD card. Press the SELECT button on the KeyPad Shield to pause the input. While the input is paused, press the SELECT button again to restart it. No IO operate will be executed if paused, so it's safe to cut off the power or remove the SD card.

This project uses Arduino UNO, SD shield and LCD KeyPad Shield.

## SD
See [Arduino - SD](http://arduino.cc/en/Reference/SD).

## LCD
See [DFRobot - Arduino LCD KeyPad Shield (SKU: DFR0009)](https://www.dfrobot.com/wiki/index.php/Arduino_LCD_KeyPad_Shield_(SKU:_DFR0009)).

## Known Problem
Both SD shield and LCD KeyPad Shield use Pin 10.
> SD shield:
> SPI, which takes place on digital pins 11, 12, and 13 (on most Arduino boards) or 50, 51, and 52 (Arduino Mega). Additionally, another pin must be used to select the SD card. This can be the hardware SS pin - pin 10 (on most Arduino boards) or pin 53 (on the Mega) - or another pin specified in the call to SD.begin(). **Note that even if you don't use the hardware SS pin, it must be left as an output or the SD library won't work.**

> LCD KeyPad Shield:
> [See the pic](https://www.dfrobot.com/wiki/images/thumb/5/5e/DFR0009-PIN2.png/1800px-DFR0009-PIN2.png)

However, if we don't try to control the LCD backlight, there seem to be no problem in the program.
