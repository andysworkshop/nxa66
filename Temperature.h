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
   
  class Temperature : public MenuItem {

    protected:
      uint32_t _lastUpdated;

    protected:
      void updateDisplay() const;

    public:
      Temperature(MenuItem *next);

      virtual void run() override;
      virtual void start() override;
  };


  /*
   * Constructor
   */

  inline Temperature::Temperature(MenuItem *next)
    : MenuItem(next,"\u0010C") {
  }


  /*
   * Startup: initialise values
   */

  inline void Temperature::start() {

    MenuItem::start();
    _lastUpdated=0;
    updateDisplay();
  }


  /*
   * looping
   */

  inline void Temperature::run() {

    if(!isStarted())
      return;

    // show the current at the top

    if(MillisecondTimer::difference(_lastUpdated)>1000) {
      _lastUpdated=MillisecondTimer::millis();
      updateDisplay();
    }
  }


  /*
   * Update the display
   */

  inline void Temperature::updateDisplay() const {
    Max7221::displayNumber(Max7221::Display::LOWER,Mcp9700::getTemperature());
  }
}
