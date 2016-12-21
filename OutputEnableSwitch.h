/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {

  /*
   * The output-enable switch is on PB7.
   */

  class OutputEnableSwitch : public Switch<GpioOutputEnableSwitch> {

    public:
      void onSwitchInterrupt();
  };


  /*
   * Constructor
   */

  inline OutputEnableSwitch::OutputEnableSwitch() {

    PCICR |= _BV(PCIE0);      // enable int group 0..7
    PCMSK0 |= _BV(PCINT7);    // enable interrupts 1,6,7

    extern OutputEnableSwitch *OutputEnableSwitchInstance;
    OutputEnableSwitchInstance=this;
  }


  /*
   * Switch interrupt
   */

  inline void OutputEnableSwitch::onSwitchInterrupt() {
    Switch<GpioOutputEnableSwitch>::onSwitchInterrupt();
  }
}
