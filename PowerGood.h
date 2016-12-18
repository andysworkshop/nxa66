/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  
  /*
   * The power-good input pin is driven low when the power is bad and pulled high
   * when it's good
   */

  class PowerGood {

    public:
      static void setup();

    public:
      static void onPowerGoodInterrupt();
      static void setLedState();
  };


  /*
   * Initialisation
   */

  inline void PowerGood::setup() {
    GpioPowerGood::setup();
    GpioPowerGoodLed::setup();

    setLedState();
  }

  inline void PowerGood::onPowerGoodInterrupt() {
    setLedState();
  }

  inline void PowerGood::setLedState() {
    GpioPowerGoodLed::changeTo(GpioPowerGood::read());
  }
}
