/*
 * Andy's Workshop Reflow Controller ATMega328p firmware
 * Copyright (c) 2015 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {


  /*
   * The voltmeter class uses the peripheral classes to read and display
   * voltage values
   */

  class Voltmeter {
    
    protected:
      enum {
        SAMPLE_INTERVAL = 100
      };

      uint32_t _lastSampleTime;

    public:
      void setup();

    public:
      void updateDisplay();
  };


  /*
   * Initialise
   */

  inline void Voltmeter::setup() {
    _lastSampleTime=0;
  }


  /*
   * Read the latest voltage and display it
   */

  inline void Voltmeter::updateDisplay() {

    // enforce a minimum sample period

    if(MillisecondTimer::difference(_lastSampleTime)<SAMPLE_INTERVAL)
      return;

    // read the voltage

    uint32_t voltage=Ina226::readBusVoltage();
    Max7221::displayFraction(Max7221::Display::UPPER,voltage);

    // read the current

    uint32_t current=Ina226::readCurrent();
    Max7221::displayFraction(Max7221::Display::LOWER,current);

    _lastSampleTime=MillisecondTimer::millis();
  }
}