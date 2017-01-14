= NXA66 Power Supply Controller Firmware

This repo contains the firmware for the power supply controller that I built to host the Artesyn NXA66 voltage regulator (power supply) module that you can pick up cheaply on ebay. You can see the full write up at my blog.

![controller](http://andybrown.me.uk/wk/wp-content/images/nxa66/running.jpg)

== Firmware installation

You don't have to compile it. In the `bin` directory you will find a `.hex` file for each release. You can flash this firmware directly to an Atmega328p using whatever utility you have available. 

I use `avrdude` and I flash directly to the Atmega328p while it's mounted in the power supply controller board using a USBASP programmer connected directly to the programming header on the controller board whilst the board is powered up. The command to do that is:

    avrdude -c usbasp -p m328p -e -U flash:w:nxa66-1.0.hex

=== Flashing the fuses

We do this step so that the Atmega328p will use its internal 8MHz RC oscillator as the MCU clock source. If your Atmega328p is fresh from the factory then you don't need to do this because the factory settings are correct. You only need to do this if your Atmega328p has been set to use an external crystal which will be the case if you've pulled it from an Arduino board.

I program my fuses using `avrdude`. You can see the command to do this in the blog article on my website. The command I use to do that is:

    avrdude -c usbasp -p m328p -e -U lfuse:w:0xe2:m -U hfuse:w:0xde:m

You can see that the low fuse value is `0xe2` and the high fuse value is `0xde`.

== Compiling from source

You can do that if you want. Make sure you've got `avr-gcc` installed. I used version `4.9.2` to build this firmware. You'll also need `scons` and `avrdude` installed and accessible.

To build the firmware, type `scons`. To build and upload directly to the board using a USBASP programmer, type `scons upload`. To burn th fuses, type `scons fuse`.
