/*
 * Andy's Workshop Reflow Controller ATMega328p firmware
 * Copyright (c) 2015 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * Main program class
   */

  class Program {

    protected:
      OutputEnableSwitch _outputEnableSwitch;
      VspSwitch _vspSwitch;
      ActionButton _actionButton;
      Encoder _encoder;
      Meter _meter;
      uint32_t _menuIdleStart;

      Limit _limit;
      Calibration _calibration;
      Intensity _intensity;
      Reset _reset;
      MenuItem *_currentMenuItem;

    protected:
      void nextMenuItem(MenuItem* next);
      void cancelMenuItem();
      void finishMenuItem();

    public:
      Program();

      void run();
  };


  /*
   * Constructor
   */

  inline Program::Program()
    : _limit(&_calibration),
      _calibration(&_intensity),
      _intensity(&_reset),
      _reset(nullptr),
      _currentMenuItem(nullptr) {
  }


  /*
   * Run this program and don't return
   */

  inline void Program::run() {

    // enable the main relay to the selected power level

    _vspSwitch.activate();

    // set the output enable to the switch state

    _outputEnableSwitch.activate();

    // enable global interrupt

    sei();

    // calibrate the INA226

    Ina226::startup();

    for(;;) {

      // always check the switches and update encoder

      _outputEnableSwitch.run();
      _vspSwitch.run();
      _encoder.run();

      // the action button needs to be sampled

      bool actionButtonChanged=_actionButton.run();

      if(_currentMenuItem==nullptr) {

        // if the action button was pressed then we enter menu mode

        if(actionButtonChanged && !_actionButton.getState()) {
          nextMenuItem(&_limit);
        }
        else
          _meter.updateDisplay();   // no relevant change, show the meter
      }
      else {

        int8_t direction;

        // loop

        _currentMenuItem->run();

        // check for the action button 

        if(actionButtonChanged && !_actionButton.getState()) {
          
          if(_currentMenuItem->isStarted()) {

            // item is running, give it a chance to consume the button
            // otherwise finish the menu item

            if(!_currentMenuItem->onActionButton())
              finishMenuItem();
          }
          else  // item is not running, start it up
            _currentMenuItem->start();

          // reset the idle timer

          _menuIdleStart=MillisecondTimer::millis();
        }
        else if((direction=_encoder.getChange())!=0) {

          // encoder has changed. if the menu item is running then it can
          // consume the encoder otherwise we move to the next item

          if(_currentMenuItem->isStarted())
            _currentMenuItem->onEncoder(direction);
          else
            nextMenuItem(_currentMenuItem->getNext() ? _currentMenuItem->getNext() : &_limit);

          // reset the idle timer

          _menuIdleStart=MillisecondTimer::millis();
        }
        else {

          // check for 10 second timeout

          if(MillisecondTimer::difference(_menuIdleStart)>10000)
            cancelMenuItem();
        }
      }
    }
  }


  /*
   * Move to the next menu item
   */

  inline void Program::nextMenuItem(MenuItem* next) {

    _currentMenuItem=next;
    _currentMenuItem->propose();
    _menuIdleStart=MillisecondTimer::millis();
  }


  /*
   * finish and confirm this item
   */

  inline void Program::finishMenuItem() {
    _currentMenuItem->finish();
    _currentMenuItem=nullptr;
  }


  /*
   * Cancel the current menu item
   */

  inline void Program::cancelMenuItem() {

    if(_currentMenuItem) {
      _currentMenuItem->cancel();
      _currentMenuItem=nullptr;
    }
  }
}
