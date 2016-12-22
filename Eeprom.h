/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  struct Eeprom {

    /*
     * EEPROM locations
     */

    enum class Location : uint8_t {
      MAGIC       = 0,      // 2 byte signature
      INTENSITY   = 2,      // 1 byte
      CALIBRATION = 3,      // 2 bytes
      MA_PER_BIT  = 5       // 1 byte
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
        static uint16_t calibration();
        static uint8_t maPerBit();
    };

    /*
     * High level write access
     */

    struct Writer {
      static void magic();
      static void constant(Location l,uint16_t c);
      static void writeByte(Location l,uint8_t b);
      static void intensity(uint8_t i);
      static void calibration(uint16_t cal);
      static void maPerBit(uint8_t ma);
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

  inline uint16_t Eeprom::Reader::calibration() {
    return eeprom_read_word(reinterpret_cast<uint16_t *>(Location::CALIBRATION));
  }


  /*
   * Read the milliamps per bit
   */

  inline uint8_t Eeprom::Reader::maPerBit() {
    return eeprom_read_byte(reinterpret_cast<uint8_t *>(Location::MA_PER_BIT));
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

  inline void Eeprom::Writer::calibration(uint16_t cal) {
    eeprom_write_word(reinterpret_cast<uint16_t *>(Location::CALIBRATION),cal);
  }


  /*
   * Write the milliamps per bit
   */

  inline void Eeprom::Writer::maPerBit(uint8_t ma) {
    eeprom_write_byte(reinterpret_cast<uint8_t *>(Location::MA_PER_BIT),ma);
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

    // based on 20A current, 2m shunt resistor, 1mA/bit resolution
    Writer::calibration(2560);
    Writer::maPerBit(1);

    Writer::magic();
  }
}

