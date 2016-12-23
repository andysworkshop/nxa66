/*
 * Andy's Workshop Reflow Controller ATMega328p firmware
 * Copyright (c) 2015 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  extern const uint8_t charTable [];

  /*
   * Handle interaction with the Max7221 SPI IC.
   */

  class Max7221 {

    public:
      
      /*
       * Register addresses
       */
      
      enum Register {
        NOP = 0,
        DIGIT0 = 1,
        DIGIT1 = 2,
        DIGIT2 = 3,
        DIGIT3 = 4,
        DIGIT4 = 5,
        DIGIT5 = 6,
        DIGIT6 = 7,
        DIGIT7 = 8,
        DECODE_MODE = 9,
        INTENSITY = 10,
        SCAN_LIMIT = 11,
        SHUTDOWN = 12,
        TEST_MODE = 15
      };

      enum Display {
        UPPER,          // the top display
        LOWER           // the bottom display
      };

    public:
      static void setup();

      static void writeByte(Register reg,uint8_t byte);
      static void writeByte(int reg,uint8_t byte);
      static void segmentMode();
      static void shutdown();
      static void wakeup();
      static void intensity(uint8_t level);

      static void clearDisplay(Display display);
      static void displayFraction(Display display,uint16_t value);
      static void displayText(Display display,const char *str);
      static void displayNumber(Display display,uint16_t value);
  };


  /*
   * Inititialise the device
   */

  inline void Max7221::setup() {

    // self test for 1 second (all digits on)

    writeByte(TEST_MODE, 1);
    MillisecondTimer::delay(1000);
    writeByte(TEST_MODE, 0);

    // enable all digits

    writeByte(SCAN_LIMIT,7);

    // set segment mode

    segmentMode();

    // blank all digits

    clearDisplay(Display::UPPER);
    clearDisplay(Display::LOWER);

    // mid intensity

    intensity(Eeprom::Reader::intensity());

    // turn on

    wakeup();
  }

  
  inline void Max7221::segmentMode() {
    writeByte(DECODE_MODE,0);
  }
  
  inline void Max7221::shutdown() {
    writeByte(SHUTDOWN,0);
  }

  inline void Max7221::wakeup() {
    writeByte(SHUTDOWN,1);
  }

  inline void Max7221::intensity(uint8_t level) {
    writeByte(INTENSITY,level);
  }

  inline void Max7221::writeByte(int reg,uint8_t byte) {
    writeByte(static_cast<Register>(reg),byte);
  }

  inline void Max7221::writeByte(Register reg, uint8_t byte) {
    GpioSpiCs::reset();
    GpioSpiMosi::writeByte(reg);
    GpioSpiMosi::writeByte(byte);
    GpioSpiCs::set();
  }

  
  /*
   * Show a fraction on the display. The value is in milli-whatever
   */

  inline void Max7221::displayFraction(Display display,uint16_t value) {

    char buffer[10];

    itoa(value/1000,buffer,10);
    sprintf(buffer+strlen(buffer),".%03d",value % 1000);
    buffer[5]='\0';

    displayText(display,buffer);
  }


  /*
   * clear down the display
   */

  inline void Max7221::clearDisplay(Display display) {

    // get first digit

    int digit=static_cast<int>(display==UPPER ? DIGIT4 : DIGIT0);
    for(int i=digit;i<digit+4;i++)
      writeByte(i,0);
  }


  /*
   * Print an integer in segment mode. The integer must not exceed 4 digits
   */

  inline void Max7221::displayNumber(Display display,uint16_t value) {

    char text[10];

    itoa(value,text,10);
    displayText(display,text); 
  }


  /*
   * Print out text to the display. str must not be more than 4
   * characters
   */

  inline void Max7221::displayText(Display display,const char *str) {

    int digit=static_cast<int>(display==UPPER ? DIGIT4 : DIGIT0);
    uint8_t count;

    count=0;
    for(const char *ptr=str;*ptr;ptr++) {
       
      uint8_t value=pgm_read_byte_near(charTable+*ptr); 
      if(ptr[1]=='.') {
        value|=0x80;
        ptr++;
      }

      writeByte(digit++,value);
      count++;
    }

    while(count<4) {
      writeByte(digit++,0);
      count++;
    }
  }
}
