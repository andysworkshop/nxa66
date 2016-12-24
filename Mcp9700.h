/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * Class to read the temperature sensor value asynchronously
   */

  class Mcp9700 {

    protected:
      volatile static uint8_t _temperature;      // temperature reading in C

    public:
      static void setup();

      static void startReading();
      static void onTimerInterrupt();
      static void onCompleteInterrupt();
      static uint8_t getTemperature();
  };


  /*
   * Setup the ADC on PC0 (ADC0)
   */

  inline void Mcp9700::setup() {

    // ADC setup

    ADMUX |= (1<<REFS0);    // Vref = Avcc
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);  // prescaler=128 (62.5kHz), enable

    // timer setup

    TCCR1A = 0;
    TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);   // clk/1024 prescaler (7812Hz), CTC mode
    
    TCNT1 = 0;                // ensure counting starts at zero
    OCR1A = 7812;             // compare target = 7812 ticks (1 second ish)
    TIMSK1 = (1 << OCIE1A);   // enable interrupts
  }


  /*
   * start a conversion on ADC0
   */

  inline void Mcp9700::startReading() {
    
    ADMUX &= 0xf0;            // enable channel 0
    ADCSRA |= (1 << ADIE);    // enable interrupts
    ADCSRA |= (1 << ADSC);    // start conversion
  }


  /*
   * Timer ticked at 1Hz, start a conversion
   */


  inline void Mcp9700::onTimerInterrupt() {
    startReading();
  }


  /*
   * Convert the reading to temperature
   */

  inline void Mcp9700::onCompleteInterrupt() {

    // low must be read first. result is right aligned (ADLAR = 0)

    uint8_t l = ADCL;
    uint8_t h = ADCH;

    // we don't need expensive floating point operations if we work in uV
    // for the calculations. The sensor outputs 10,000uV/C with 500,000uV at 0C.
    // the Atmega 10 bit ADC is equivalent to 4882uV per-bit with Vref = 5V

    uint32_t result=l | (static_cast<uint32_t>(h) << 8);

    result*=4882;           // convert bits to uV
    result-=500000;         // subtract the zero reading (500uV)
    result/=10000;          // scale uV to C (10,000uV / C)

    _temperature=result;    // we're in the 8-bit range now
  }


  /*
   * Read the last temperature value. 
   */

  inline uint8_t Mcp9700::getTemperature() {
    return _temperature;
  }
}
