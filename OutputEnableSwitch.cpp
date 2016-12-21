/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#include "Application.h"


namespace nxa66 {
  OutputEnableSwitch *OutputEnableSwitchInstance;
}


ISR(PCINT7_vect) {
  if(OutputEnableSwitchInstance)
    OutputEnableSwitchInstance->onSwitchInterrupt();
}
