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
      Meter _meter;

    public:
      void run();
  };


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

      _outputEnableSwitch.run();
      _vspSwitch.run();

      _meter.updateDisplay();
    }
  }
}
