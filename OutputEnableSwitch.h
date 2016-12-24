/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {

  /*
   * The output-enable switch is on PB7.
   */

  struct OutputEnableSwitch : Switch<GpioOutputEnableSwitch> {
    void run();
    void activate();
  };


  /*
   * Main loop
   */

  inline void OutputEnableSwitch::run() {

    // check if the switch changed

    if(!Switch<GpioOutputEnableSwitch>::run())
      return;

    activate();
  }


  inline void OutputEnableSwitch::activate() {

    // switch is active low

    if(getState())
      OutputEnable::disable();
    else
      OutputEnable::enable();
  }
}
