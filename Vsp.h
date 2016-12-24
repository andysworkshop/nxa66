/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {


  /*
   * Handle the VSP (voltage output select) line. This cannot be changed while the
   * module is powered up so we shut it down while changing.
   */

  struct Vsp {
    static void setup();

    static void normal();
    static void vsp();
  };


  inline void Vsp::setup() {
    GpioVsp::setup();
  }

  inline void Vsp::normal() {
    PowerOn::disable();
    GpioVsp::reset();
    PowerOn::enable();
  }

  inline void Vsp::vsp() {
    PowerOn::disable();
    GpioVsp::set();
    PowerOn::enable();
  }
}
