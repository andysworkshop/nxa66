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

      Intensity _intensity;
      MenuItem *_currentMenuItem;

    protected:
      void nextMenuItem(MenuItem* next);
      void cancelMenuItem();

    public:
      Program();

      void run();
  };


  /*
   * Constructor
   */

  inline Program::Program()
    : _intensity(nullptr),
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

    Ina226::calibrate();

    for(;;) {

      // always check the switches and update encoder

      _outputEnableSwitch.run();
      _vspSwitch.run();
      _encoder.run();

      // the action button needs to be sampled

      bool actionButtonChanged=_actionButton.run();

      if(_currentMenuItem==null) {

        // if the action button was pressed then we enter menu mode

        if(actionButtonChanged && !_actionButton.getState()) 
          nextMenuItem(&_intensity);
        else {
          _meter.updateDisplay();   // no relevant change, show the meter
      }
      else {

        int8_t direction;

        // check for the action button - move to next menu 

        if(actionButtonChanged && !_actionButton.getState())
          nextMenuItem(_currentMenuItem->getNext());
        else if((direction=_encoder.getChange())!=0) {

          // encode moved, pass on
          
          _currentMenuItem->onEncoder(direction);
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

    // finish the current item if there is one

    if(_currentMenuItem)
      _currentMenuItem->finish();

    // set the new one and start if required

    _currentMenuItem=next;

    if(_currentMenuItem) {
      _currentMenuItem->start();
      _menuIdleStart=MillisecondTimer::millis();
    }
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
