/*
 * Andy's Workshop Reflow Controller ATMega328p firmware
 * Copyright (c) 2015 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {


  /*
   * The meter class uses the peripheral classes to read and display
   * voltage values
   */

  class Meter {
    
    protected:
      enum {
        SAMPLE_INTERVAL = 200
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

  inline void Meter::setup() {
    _lastSampleTime=0;
  }


  /*
   * Read the latest voltage and display it
   */

  inline void Meter::updateDisplay() {

    // enforce a minimum sample period

    if(MillisecondTimer::difference(_lastSampleTime)<SAMPLE_INTERVAL)
      return;

    // read the voltage

    uint32_t voltage=Ina226::readBusVoltage();
    Max7221::displayFraction(Max7221::Display::UPPER,voltage);

    // read the current

    uint32_t current=Ina226::readCurrent();

    // 65535 or near enough is returned when open loop. anything greater
    // than our max current blanks the display
    
    if(current>25000)
      Max7221::clearDisplay(Max7221::Display::LOWER);
    else
      Max7221::displayFraction(Max7221::Display::LOWER,current);

    _lastSampleTime=MillisecondTimer::millis();
  }
}