/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#include "Application.h"

ISR(INT0_vect) {
  nxa66::PowerGood::onPowerGoodInterrupt();
}
