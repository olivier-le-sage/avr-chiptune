# avr-chiptune

![If music be the food of love, play on!](assets/sheet_music.PNG?raw=true "")

## Summary

A brief program that plays a pre-written chiptune melody on an Atmel ATtiny10 microprocessor
that, in its SOT-23 packaging, is smaller than a grain of rice.
The music is played with a small piezoelectric sensor (buzzer).
Classical audiophiles may recognize Bach's Toccata and Fugue in D minor.

It fits into 1024 bytes of program memory and 32 bytes of SRAM, so it should work on any
AVR microprocesor with the same architecture/registers.

## Schematic

![Hardware diagram](assets/schematic.png?raw=true "")

## Pre-requisites

This project requires the avr-libc SDK and the AVR GCC compiler. They can be
installed on Debian systems by using the following command:

```
sudo apt-get install avr-libc gcc-avr build-essential git
```

You can check that avr-gcc is installed by calling *avr-gcc --version*.

## References

ATtiny4/5/9/10 Datasheet:
- http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8127-AVR-8-bit-Microcontroller-ATtiny4-ATtiny5-ATtiny9-ATtiny10_Datasheet.pdf

avr-libc Linux package:
- https://nongnu.org/avr-libc/user-manual/index.html
