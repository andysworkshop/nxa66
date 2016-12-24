/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {


  /*
   * Current limit adjustment between 10mA and 20A in 10mA steps. 
   */

  class FanThreshold : public MenuItem {

    protected:
      uint8_t _on;
      uint8_t _off;

      enum Adjustment {
        ON,
        OFF
      } _adjustment;

    protected:
      void updateDisplay() const;

    public:
      FanThreshold(MenuItem *next);

      virtual void start() override;
      virtual void finish() override;
      virtual void onEncoder(int8_t direction) override;
      virtual bool onActionButton() override;
  };


  /*
   * Constructor
   */

  inline FanThreshold::FanThreshold(MenuItem *next)
    : MenuItem(next,"FAn") {
  }


  /*
   * Startup: initialise values
   */

  inline void FanThreshold::start() {

    MenuItem::start();

    _on=Eeprom::Reader::fanOn();
    _off=Eeprom::Reader::fanOff();
    _adjustment=ON;

    Max7221::writeByte(Max7221::DIGIT7,0b01000000);   // high indicator
    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void FanThreshold::finish() {
    Eeprom::Writer::fanOn(_on);
    Eeprom::Writer::fanOff(_off);
  }


  /*
   * Encoder (wheel) changed
   */

  inline void FanThreshold::onEncoder(int8_t direction) {

    if(direction>0) {
      if(_adjustment==ON) {
        if(_on<200)
          _on++;
      }
      else {
        if(_off<200)
          _off++;
      }
    }
    else if(direction<0) {
      if(_adjustment==ON) {
        if(_on)
          _on--;
      }
      else {
        if(_off)
          _off--;
      }
    }

    updateDisplay();
  }


  /*
   * Action button pressed
   */

  inline bool FanThreshold::onActionButton() {

    // intercept for adjustment on->off

    if(_adjustment==ON) {
      _adjustment=OFF;
      Max7221::writeByte(Max7221::DIGIT7,0b00001000);   // low indicator
      updateDisplay();
      return true;
    }

    return false;
  }


  /*
   * Update the display
   */

  inline void FanThreshold::updateDisplay() const {
    Max7221::displayNumber(Max7221::Display::LOWER,_adjustment==ON ? _on : _off);
  }
}
