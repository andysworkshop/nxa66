/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * General utilities to read/write configuration values to the EEPROM. Functionality
   * is divided between Reader and Writer classes.
   */
   
  struct Eeprom {

    /*
     * EEPROM locations
     */

    enum class Location : uint8_t {
      MAGIC       = 0,      // 2 byte signature
      INTENSITY   = 2,      // 1 byte (8)
      CALIBRATION = 3,      // 2 bytes (0)
      ILIMIT      = 5,      // 2 bytes (20000)
      LOGGER      = 7,      // 2 bytes (1000)
      FAN_ON      = 9,      // 1 byte fan on temperature (40)
      FAN_OFF     = 10,     // 1 byte fan off temperature (30)
    };


    /*
     * The magic number that indicates valid EEPROM content
     */

    enum {
      MAGIC_NUMBER = 0xaa55
    };


    static void verifyState();
    static void writeDefaults();

    /*
     * High level read access
     */

    class Reader {
      
      protected:
        static uint16_t validate(uint16_t value);

      public:
        static uint16_t magic();
        static uint16_t constant(Location l);
        static uint8_t readByte(Location l);
        static uint8_t intensity();
        static int16_t calibration();
        static uint16_t currentLimit();
        static uint16_t loggerInterval();
        static uint8_t fanOn();
        static uint8_t fanOff();
    };

    /*
     * High level write access
     */

    struct Writer {
      static void magic();
      static void constant(Location l,uint16_t c);
      static void writeByte(Location l,uint8_t b);
      static void intensity(uint8_t i);
      static void calibration(int16_t cal);
      static void currentLimit(uint16_t limit);
      static void loggerInterval(uint16_t interval);
      static void fanOn(uint8_t temp);
      static void fanOff(uint8_t temp);
    };
  };


  /*
   * Read a byte
   */

  inline uint8_t Eeprom::Reader::readByte(Location l) {
    return eeprom_read_byte(reinterpret_cast<uint8_t *>(l));
  }


  /*
   * Read a constant value
   */

  inline uint16_t Eeprom::Reader::constant(Location l) {
    return eeprom_read_word(reinterpret_cast<uint16_t *>(l));
  }


  /*
   * Read the magic number
   */

  inline uint16_t Eeprom::Reader::magic() {
    return eeprom_read_word(reinterpret_cast<uint16_t *>(Location::MAGIC));
  }


  /*
   * Read the LCD intensity value (0..15)
   */

  inline uint8_t Eeprom::Reader::intensity() {
    return eeprom_read_byte(reinterpret_cast<uint8_t *>(Location::INTENSITY));
  }


  /*
   * Read the INA226 calibration value
   */

  inline int16_t Eeprom::Reader::calibration() {
    return eeprom_read_word(reinterpret_cast<uint16_t *>(Location::CALIBRATION));
  }


  /*
   * Read the current limit
   */

  inline uint16_t Eeprom::Reader::currentLimit() {
    return eeprom_read_word(reinterpret_cast<uint16_t *>(Location::ILIMIT));
  }


  /*
   * Read the logger interval
   */

  inline uint16_t Eeprom::Reader::loggerInterval() {
    return eeprom_read_word(reinterpret_cast<uint16_t *>(Location::LOGGER));
  }


  /*
   * Read the fan on temperature
   */

  inline uint8_t Eeprom::Reader::fanOn() {
    return eeprom_read_byte(reinterpret_cast<uint8_t *>(Location::FAN_ON));
  }


  /*
   * Read the fan on temperature
   */

  inline uint8_t Eeprom::Reader::fanOff() {
    return eeprom_read_byte(reinterpret_cast<uint8_t *>(Location::FAN_OFF));
  }


  /*
   * Write a byte to the location
   */

  inline void Eeprom::Writer::writeByte(Location l,uint8_t b) {
    eeprom_write_byte(reinterpret_cast<uint8_t *>(l),b);
  }


  /*
   * Write a constant value
   */

  inline void Eeprom::Writer::constant(Location l,uint16_t c) {
    eeprom_write_word(reinterpret_cast<uint16_t *>(l),c);
  }


  /*
   * Write the magic number
   */

  inline void Eeprom::Writer::magic() {
    eeprom_write_word(reinterpret_cast<uint16_t *>(Location::MAGIC),MAGIC_NUMBER);
  }


  /*
   * Write the intensity
   */

  inline void Eeprom::Writer::intensity(uint8_t i) {
    eeprom_write_byte(reinterpret_cast<uint8_t *>(Location::INTENSITY),i);
  }


  /*
   * Write the calibration
   */

  inline void Eeprom::Writer::calibration(int16_t cal) {
    eeprom_write_word(reinterpret_cast<uint16_t *>(Location::CALIBRATION),cal);
  }


  /*
   * Write the current limit
   */

  inline void Eeprom::Writer::currentLimit(uint16_t limit) {
    eeprom_write_word(reinterpret_cast<uint16_t *>(Location::ILIMIT),limit);
  }


  /*
   * Write the logger interval
   */

  inline void Eeprom::Writer::loggerInterval(uint16_t interval) {
    eeprom_write_word(reinterpret_cast<uint16_t *>(Location::LOGGER),interval);
  }


  /*
   * Write the fan on temperature
   */

  inline void Eeprom::Writer::fanOn(uint8_t temp) {
    eeprom_write_byte(reinterpret_cast<uint8_t *>(Location::FAN_ON),temp);
  }


  /*
   * Write the fan off temperature
   */

  inline void Eeprom::Writer::fanOff(uint8_t temp) {
    eeprom_write_byte(reinterpret_cast<uint8_t *>(Location::FAN_OFF),temp);
  }


  /*
   * Verify the content and default it if invalid
   */

  inline void Eeprom::verifyState() {
   
    // check for the signature and return if OK

    if(Reader::magic()==MAGIC_NUMBER)
      return;

    writeDefaults();
  }


  /*
   * Write the default values to EEPROM
   */

  inline void Eeprom::writeDefaults() {

    // write out default content

    Writer::intensity(8);

    Writer::calibration(0);
    Writer::currentLimit(20000);
    Writer::loggerInterval(1000);
    Writer::fanOn(40);
    Writer::fanOff(30);
    Writer::magic();
  }
}

