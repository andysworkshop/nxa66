/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {

  /*
   * The power-on line controls the relay that supplies power to the module. The relay has a maximum
   * switching time of about 15ms. We use a delay of 100ms to be sure. 
   */

  class PowerOn {

    public:
      static void setup();

      static void enable();
      static void disable();
  };
  

  inline void PowerOn::setup() {
    GpioPowerOn::setup();
  }

  inline void PowerOn::enable() {
    GpioPowerOn::set();
    MillisecondTimer::delay(100);
  }

  inline void PowerOn::disable() {
    GpioPowerOn::reset();
    MillisecondTimer::delay(100);
  }
}
