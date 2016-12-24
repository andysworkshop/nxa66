/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {

  /*
   * The output-enable line controls the EN pin of the supply.
   */

  struct OutputEnable {
    static void setup();

    static void enable();
    static void disable();
  };
  

  inline void OutputEnable::setup() {
    GpioOutputEnable::setup();
  }

  inline void OutputEnable::enable() {
    GpioOutputEnable::reset();
  }

  inline void OutputEnable::disable() {
    GpioOutputEnable::set();
  }
}