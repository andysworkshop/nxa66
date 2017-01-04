/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {

  /*
   * The Action button is on PC1. It's just a switch, so we don't
   * need any more functionality than that provided by the template.
   */

  typedef Switch<GpioActionButton> ActionButton;
}
