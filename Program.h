/*
 * Andy's Workshop Reflow Controller ATMega328p firmware
 * Copyright (c) 2015 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * Main program class
   */

  class Program {

    protected:
      OutputEnableSwitch _outputEnableSwitch;
      Meter _meter;

    public:
      Program();

      void run();
  };


  /*
   * Constructor: all GPIO pins are initialised here
   */

  inline Program::Program() {

    // SPI limiting values:
    // Selected clock is osc/2, mode is 0

    SPCR=(1 << MSTR) |                  // master
         (1 << SPE) |                   // enabled
         (0 << SPR1) | (0 << SPR0);     // (for clarity) we are intentionally choosing fosc/4 here

    SPSR |= (1 << SPI2X);               // double the fosc/4 to get fosc/2

    // clear interrupt flag by reading this register

    uint8_t dummy __attribute__((unused))=SPSR;
    dummy=SPDR;

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
    Vsp::normal();

    PowerGood::setup();
    Wire.begin();
  }


  /*
   * Run this program and don't return
   */

  inline void Program::run() {

    // enable the main relay

    PowerOn::enable();
  //  OutputEnable::disable();
    OutputEnable::enable();

    // enable global interrupt

    sei();

    // calibrate the INA226

    Ina226::calibrate();

    for(;;) {
      _meter.updateDisplay();
    }
  }
}
