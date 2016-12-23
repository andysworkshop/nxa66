/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

 #include "Application.h"


/*
 * Main entry point. Note that the fuse settings for the application
 * should be set for the internal 8MHz oscillator.
 */

int main() {

  using namespace nxa66;
  
  // disable watchdog in case we got here from a software reset

  MCUSR = 0;
  wdt_disable();

  // interrupts off

  cli();

  // SPI limiting values:
  // Selected clock is osc/2, mode is 0

  SPCR=(1 << MSTR) |                  // master
       (1 << SPE) |                   // enabled
       (0 << SPR1) | (0 << SPR0);     // (for clarity) we are intentionally choosing fosc/4 here

  SPSR |= (1 << SPI2X);               // double the fosc/4 to get fosc/2

  // clear interrupt flag by reading this register

  uint8_t dummy __attribute__((unused))=SPSR;
  dummy=SPDR;

  // EEPROM validation

  Eeprom::verifyState();

  // UART pins

  GpioUartTx::setup();
  GpioUartRx::setup();
  GpioUartRx::set();    // pullup

  // setup the SPI pins

  GpioSpiCs::setup();
  GpioSpiCs::set();

  GpioSpiMosi::setup();
  GpioSpiClk::setup();

  //  encoder pins with pullups

  GpioEncoderA::setup();
  GpioEncoderB::setup();

  GpioEncoderA::set();
  GpioEncoderB::set();

  // action button with pullup

  GpioActionButton::setup();
  GpioActionButton::set();

  // switches with pullups

  GpioOutputEnableSwitch::setup();
  GpioOutputEnableSwitch::set();

  GpioVspSwitch::setup();
  GpioVspSwitch::set();

  // initialisers

  MillisecondTimer::setup();
  Max7221::setup();

  PowerOn::setup();

  OutputEnable::setup();
  OutputEnable::disable();

  Vsp::setup();

  PowerGood::setup();
  Wire.begin();

  Uart::setup();

  // declare the program class

  nxa66::Program p;
  p.run(); 
 
  // not reached

  return 0;
}
