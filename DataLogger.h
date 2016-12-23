/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {


  /*
   * Data logger class uses the UART to periodically send measurement data from
   * the INA226. Data format is 19200bps 8-N-1. The TX interval is configurable.
   */

  class DataLogger {

    public:
      uint32_t _lastSendTime;

    public:
      DataLogger();

      void run();
  };


  /*
   * Constructor
   */

  inline DataLogger::DataLogger()
    : _lastSendTime(0) {

  }


  /*
   * Main loop
   */

  inline void DataLogger::run() {

    // do nothing until logging interval has passed or if disabled

    uint16_t interval=Eeprom::Reader::loggerInterval();

    if(!interval || MillisecondTimer::difference(_lastSendTime)<interval)
      return;

    // get values to send

    _lastSendTime=MillisecondTimer::millis();
    uint16_t voltage=Ina226::readBusVoltage();
    uint16_t current=Ina226::readCurrent();

    char buffer[40];
    sprintf(buffer,"%lu|%u|%u\r\n",_lastSendTime,voltage,current);

    Uart::sendString(buffer,strlen(buffer));
  }
}