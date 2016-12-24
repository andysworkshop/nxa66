/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#include "Application.h"


namespace nxa66 {
  volatile uint8_t Mcp9700::_temperature = 0;
}


/*
 * ADC conversion complete
 */

ISR(ADC_vect) {
  nxa66::Mcp9700::onCompleteInterrupt();
}


/*
 * Timer ticked
 */

ISR(TIMER1_COMPA_vect) {
  nxa66::Mcp9700::onTimerInterrupt();
}
