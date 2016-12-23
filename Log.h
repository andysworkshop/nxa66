/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  class Log : public MenuItem {

    protected:
      uint16_t _interval;

    protected:
      void updateDisplay() const;

    public:
      Log(MenuItem *next);

      virtual void start() override;
      virtual void finish() override;
      virtual void onEncoder(int8_t direction) override;
  };


  /*
   * Constructor
   */

  inline Log::Log(MenuItem *next)
    : MenuItem(next,"Log") {
  }


  /*
   * Startup: initialise values
   */

  inline void Log::start() {

    MenuItem::start();

    _interval=Eeprom::Reader::loggerInterval();
    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void Log::finish() {
    Eeprom::Writer::loggerInterval(_interval);
  }


  /*
   * Encoder (wheel) changed
   */

  inline void Log::onEncoder(int8_t direction) {

    if(direction>0) {
      if(_interval<65500)
        _interval+=100;
    }
    else if(direction<0) {
      if(_interval)
        _interval-=100;
    }

    updateDisplay();
  }


  /*
   * Update the display
   */

  inline void Log::updateDisplay() const {
    Max7221::displayNumber(Max7221::Display::LOWER,_interval);
  }
}
