/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  class Ina226 {

    protected:
      enum {
        ADDRESS = 0x40,

        CONFIGURATION = 0,
        SHUNT_VOLTAGE = 0x01,
        BUS_VOLTAGE = 0x02,
        POWER = 0x03,
        CURRENT = 0x04,
        CALIBRATION = 0x05,
        MANUFACTURER_ID = 0xfe
      };

    protected:
      static uint16_t readRegister(uint8_t reg);
      static void writeRegister(uint8_t reg,uint16_t value);

    public:
      static uint32_t readShuntVoltage();
      static uint32_t readBusVoltage();
      static uint32_t readCurrent();

      static void calibrate();
  };


  /*
   * Write the calibration value
   */

  inline void Ina226::calibrate() {

    // first write the configuration register

    uint16_t averaging = 2;       // 16x averaging
    uint16_t vbuscvt = 4;         // 1.1ms conversion time
    uint16_t shuntcvt = 4;        // 1.1ms conversion time
    uint16_t opmode = 7;          // shunt and bus, continuous

    uint16_t cfg = 0x4000 | (averaging << 9) | (vbuscvt << 6) | (shuntcvt << 3) | opmode;
    writeRegister(CONFIGURATION,cfg);
  }


  /*
   * Read the value of the voltage across the shunt resistor in uV
   */

  inline uint32_t Ina226::readShuntVoltage() {
    return readRegister(SHUNT_VOLTAGE)*250l/100l;
  }

  
  /*
   * Read the value of the bus voltage in mV.
   */

  inline uint32_t Ina226::readBusVoltage() {
    return (readRegister(BUS_VOLTAGE)*125l)/100l;
  }


  /*
   * Read the current flowing through the shunt resistor in mA
   */

  inline uint32_t Ina226::readCurrent() {
    return readRegister(CURRENT);
  }


  /*
   * Read a value from a register
   */

  inline uint16_t Ina226::readRegister(uint8_t reg) {

    Wire.beginTransmission(ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();
      
    Wire.requestFrom(ADDRESS,2);
    while(Wire.available()!=2);

    uint16_t value=Wire.read();
    return value << 8 | Wire.read();
  }


  /*
   * Write a value to a register
   */

  inline void Ina226::writeRegister(uint8_t reg,uint16_t value) {

    Wire.beginTransmission(ADDRESS);
    Wire.write(reg);
    Wire.write(value >> 8);
    Wire.write(value & 0xff);
    Wire.endTransmission();
  }
}
