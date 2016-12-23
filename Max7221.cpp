/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#include "Application.h"


namespace nxa66 {

  const uint8_t charTable [] PROGMEM  = {
      0b01111110,
      0b00110000,
      0b01101101,
      0b01111001,
      0b00110011,
      0b01011011,
      0b01011111,
      0b01110000,
      0b01111111,
      0b01111011,
      0b01110111,
      0b00011111,
      0b00001101,
      0b00111101,
      0b01001111,
      0b01000111,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b10000000,
      0b00000001,
      0b10000000,
      0b00000000,
      0b01111110,
      0b00110000,
      0b01101101,
      0b01111001,
      0b00110011,
      0b01011011,
      0b01011111,
      0b01110000,
      0b01111111,
      0b01111011,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b01110111,
      0b00011111,
      0b01001110,   // C
      0b00111101,
      0b01001111,
      0b01000111,
      0b00000000,
      0b00110111,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00001110,
      0b00000000,
      0b00000000,
      0b00000000,
      0b01100111,
      0b00000000,
      0b00000000,
      0b01011011,   // S
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00001000,
      0b00000000,
      0b01110111,
      0b00011111,
      0b00001101,
      0b00111101,
      0b01001111,
      0b01000111,
      0b00000000,
      0b00110111,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00001110,
      0b00000000,
      0b00010101,
      0b00011101,
      0b01100111,
      0b00000000,
      0b00000101,   // r
      0b00000000,
      0b00001111,   // t 
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00111011,   // y
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000
  };
}
