/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {

  /*
   * The VSP switch is on PB6.
   */

  struct VspSwitch : Switch<GpioVspSwitch> {
    void run();
    void activate();
  };


  /*
   * Switch interrupt
   */

  inline void VspSwitch::run() {

    // check if the switch changed

    if(!Switch<GpioVspSwitch>::run())
      return;

    activate();
  }


  inline void VspSwitch::activate() {

    // switch is active low
    
    if(getState())
      Vsp::vsp();
    else
      Vsp::normal();
  }
}
