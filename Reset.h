/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  class Reset : public MenuItem {

    protected:
      bool _confirm;

    protected:
      void updateDisplay() const;

    public:
      Reset(MenuItem *next);

      virtual void start() override;
      virtual void finish() override;
      virtual void onEncoder(int8_t direction) override;
  };


  /*
   * Constructor
   */

  inline Reset::Reset(MenuItem *next)
    : MenuItem(next,"rSEt") {
  }


  /*
   * Startup: initialise values
   */

  inline void Reset::start() {

    MenuItem::start();

    _confirm=true;
    updateDisplay();
  }


  /*
   * User has confirmed completion with the action button
   */

  inline void Reset::finish() {

    if(!_confirm)
      return;

    // write default settings and do a software reset after 500ms
    // the relatively long delay allows us to disable watchdog
    // in the startup code

    Eeprom::writeDefaults();
    wdt_enable(WDTO_500MS);
    while(1);
  }


  /*
   * Encoder (wheel) changed
   */

  inline void Reset::onEncoder(int8_t /* direction */) {
    _confirm^=true;
    updateDisplay();
  }


  /*
   * Update the display
   */

  inline void Reset::updateDisplay() const {
    Max7221::displayText(Max7221::Display::LOWER,_confirm ? "yES" : "no");
  }
}
