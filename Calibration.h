/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  class Calibration : public MenuItem {

    protected:
      int16_t _calibration;
      uint32_t _lastUpdated;

    protected:
      void updateDisplay() const;

    public:
      Calibration(MenuItem *next);

      virtual void run() override;
      virtual void start() override;
      virtual void finish() override;
      virtual void cancel() override;
      virtual void onEncoder(int8_t direction) override;
  };


  /*
   * Constructor
   */

  inline Calibration::Calibration(MenuItem *next)
    : MenuItem(next,"CAL") {
  }


  /*
   * looping
   */

  inline void Calibration::run() {

    if(!isStarted())
      return;

    // show the current at the top

    if(MillisecondTimer::difference(_lastUpdated)>200) {
      Meter::updateCurrentDisplay(Max7221::Display::UPPER);
      _lastUpdated=MillisecondTimer::millis();
    }
  }


  /*
   * Startup: initialise values
   */

  inline void Calibration::start() {

    MenuItem::start();

    _calibration=Eeprom::Reader::calibration();
    _lastUpdated=0;
    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void Calibration::finish() {
    Eeprom::Writer::calibration(_calibration);
  }


  /*
   * Cancel by timeout
   */

  inline void Calibration::cancel() {
    Ina226::calibrate();
  }


  /*
   * Encoder (wheel) changed
   */

  inline void Calibration::onEncoder(int8_t direction) {

    if(direction>0) {
      if(_calibration<999)
        _calibration++;
    }
    else if(direction<0) {
      if(_calibration>-999)
        _calibration--;
    }

    Ina226::calibrateWith(_calibration);
    updateDisplay();
  }


  /*
   * Update the display
   */

  inline void Calibration::updateDisplay() const {

    // calibration value at the bottom

    Max7221::displayNumber(Max7221::Display::LOWER,_calibration);
  }
}
