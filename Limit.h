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

  class Limit : public MenuItem {

    protected:
      uint16_t _limit;
      enum Adjustment {
        AMPS,
        MILLIAMPS
      } _adjustment;

    protected:
      void updateDisplay() const;

    public:
      Limit(MenuItem *next);

      virtual void start() override;
      virtual void finish() override;
      virtual void onEncoder(int8_t direction) override;
      virtual bool onActionButton() override;
  };


  /*
   * Constructor
   */

  inline Limit::Limit(MenuItem *next)
    : MenuItem(next,"IL") {
  }


  /*
   * Startup: initialise values
   */

  inline void Limit::start() {

    MenuItem::start();

    _limit=Eeprom::Reader::currentLimit();
    _adjustment=AMPS;

    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void Limit::finish() {
    Eeprom::Writer::currentLimit(_limit);
  }


  /*
   * Encoder (wheel) changed
   */

  inline void Limit::onEncoder(int8_t direction) {

    if(direction>0) {

      _limit+=_adjustment==AMPS ? 1000 : 10;
      
      if(_limit>20000)
        _limit=20000;
    }
    else if(direction<0) {

      if(_adjustment==AMPS)
        _limit=_limit>1010 ? _limit-1000 : 10;
      else
        _limit=_limit>10 ? _limit-10 : 10;
    }

    updateDisplay();
  }


  /*
   * Action button pressed
   */

  inline bool Limit::onActionButton() {

    // intercept for adjustment amps->milliamps

    if(_adjustment==AMPS) {
      _adjustment=MILLIAMPS;
      return true;
    }

    return false;
  }


  /*
   * Update the display
   */

  inline void Limit::updateDisplay() const {
    Max7221::displayFraction(Max7221::Display::LOWER,_limit);
  }
}
