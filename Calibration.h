/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * INA226 current measurement calibration adjustment. Allows +/- 999 points to be added to
   * the calibration value so that the displayed current can be made to match that of a
   * calibrated measuring instrument
   */
   
  class Calibration : public MenuItem {

    protected:
      enum {
        DISPLAY_UPDATE_INTERVAL = 200
      };
      
      int16_t _calibration;       // read from EEPROM
      uint32_t _lastUpdated;      // last time we updated the current display

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
   * Constructor: set up the menu prompt
   */

  inline Calibration::Calibration(MenuItem *next)
    : MenuItem(next,"CAL") {
  }


  /*
   * looping
   */

  inline void Calibration::run() {

    // nothing to do until the user selects this menu item

    if(!isStarted())
      return;

    // show the current at the top every 

    if(MillisecondTimer::difference(_lastUpdated)>DISPLAY_UPDATE_INTERVAL) {
      Meter::updateCurrentDisplay(Max7221::Display::UPPER);
      _lastUpdated=MillisecondTimer::millis();
    }
  }


  /*
   * Startup: initialise values
   */

  inline void Calibration::start() {

    // always call the base class

    MenuItem::start();

    // initialise by reading from EEPROM and update the display

    _calibration=Eeprom::Reader::calibration();
    _lastUpdated=0;
    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void Calibration::finish() {
    
    // write back the new calibration value to EEPROM

    Eeprom::Writer::calibration(_calibration);
  }


  /*
   * Cancel by timeout
   */

  inline void Calibration::cancel() {
    
    // cancel by restoring the old calibration value

    Ina226::calibrate();
  }


  /*
   * Encoder (wheel) changed
   */

  inline void Calibration::onEncoder(int8_t direction) {

    // adjust to a new setting

    if(direction>0) {
      if(_calibration<999)
        _calibration++;
    }
    else if(direction<0) {
      if(_calibration>-999)
        _calibration--;
    }

    // set the calibration value
    
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
