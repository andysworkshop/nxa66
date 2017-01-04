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
   * The data format is:
   *
   * timestamp|voltage|current|crc\r\n
   *
   * The timestamp is in milliseconds since the firmware started its millisecond
   * timer. The voltage is in mV. The current is in mA. The CRC is the 8-bit
   * CCITT standard and covers characters from the first in the line up to and
   * including the vertical bar before the CRC itself.
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
   * Main loop. Poll this regularly.
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

    char buffer[50];
    sprintf(buffer,"%lu|%u|%u|",_lastSendTime,voltage,current);

    // calculate the 8-bit CRC of the characters so far

    uint8_t crc=0;
    char *ptr;
    
    for(ptr=buffer;*ptr;ptr++)
      crc=_crc8_ccitt_update(crc,*ptr);

    // tack on the CRC to the end of the buffer

    sprintf(ptr,"%u\r\n",static_cast<uint16_t>(crc));

    // send asynchronously

    Uart::sendString(buffer,strlen(buffer));
  }
}
