/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#include "Application.h"


namespace nxa66 {

  // static definitions

  volatile const char *Uart::_txptr=nullptr;
  volatile uint8_t Uart::_txlen=0;
}


/*
 * TX interrupt vector
 */

ISR(USART_UDRE_vect) {
  nxa66::Uart::onTransmitInterrupt();
}
