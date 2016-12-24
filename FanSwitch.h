/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {


  /*
   * The fan switch is a MOSFET
   */

  struct FanSwitch {
    static void enable();
    static void disable();
  };


  /*
   * Switch the fan on
   */

  inline void FanSwitch::enable() {
    GpioFanSwitch::set();
  }


  /*
   * Switch the fan off
   */

  inline void FanSwitch::disable() {
    GpioFanSwitch::reset();
  }
}