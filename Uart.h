/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * The UART peripheral class handles sending data. Data is transmitted
   * asynchronously using the UDRIE interrupt.
   */

  class Uart {

    protected:
      volatile static const char *_txptr;
      volatile static uint8_t _txlen;

    public:
      static void setup();
      static void sendString(const char *buffer,uint8_t size);

      static void onTransmitInterrupt();
  };


  /*
   * setup the pins
   */

  inline void Uart::setup() {

    UBRR0 = 25;                               // 19200 bps
    UCSR0B |= (1 << TXEN0);                   // enable TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8-N-1
  }


  /*
   * send up to 255 characters
   */

  inline void Uart::sendString(const char *buffer,uint8_t size) {

    // cannot clobber an existing in-progress transmission

    if(_txlen)
      return;
    
    // set up parameters

    _txptr=buffer;
    _txlen=size;

    // enable interrupts

    UCSR0B |= (1 << UDRIE0);
  }


  /*
   * TX interrupt fired
   */

  inline void Uart::onTransmitInterrupt() {

    // prepare to send this character

    UDR0=*_txptr++;

    // update counter and if at zero then we're done interrupting

    _txlen--;
    if(!_txlen)
      UCSR0B &=~ (1 << UDRIE0);
  }
}
