/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  class Intensity : public MenuItem {

    protected:
      uint8_t _intensity;

    protected:
      void updateDisplay() const;

    public:
      Intensity(MenuItem *next);

      virtual void start() override;
      virtual void finish() override;
      virtual void cancel() override;
      virtual void onEncoder(int8_t direction) override;
  };


  /*
   * Constructor
   */

  inline Intensity::Intensity(MenuItem *next)
    : MenuItem(next) {
  }


  /*
   * Startup: initialise values
   */

  inline void Intensity::start() {
    _intensity=Eeprom::Reader::intensity();
    Max7221::displayText(Max7221::Display::UPPER,"LED");
    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void Intensity::finish() {
    Eeprom::Writer::intensity(_intensity);
  }


  /*
   * Cancel by timeout
   */

  inline void Intensity::cancel() {
    Max7221::intensity(Eeprom::Reader::intensity());
  }


  /*
   * Encoder (wheel) changed
   */

  inline void Intensity::onEncoder(int8_t direction) {

    if(direction>0) {
      if(_intensity<15)
        _intensity++;
    }
    else if(direction<0) {
      if(_intensity)
        _intensity--;
    }

    updateDisplay();
  }


  /*
   * Update the display
   */

  inline void Intensity::updateDisplay() const {
    Max7221::displayNumber(Max7221::Display::LOWER,_intensity);
    Max7221::intensity(_intensity);
  }
}
