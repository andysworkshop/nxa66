/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once


namespace nxa66 {

  /*
   * Abstract base for menu items. I normally stay away from virtual methods
   * in embedded applications because the vtable is copied to SRAM on startup
   * but in this application SRAM resources are not under pressure so I can
   * afford this luxury.
   */

  class MenuItem {

    protected:
      enum State {
        NONE,
        PROPOSED,
        STARTED
      } _state;

      const char *_title;
      MenuItem *_next;

    public:
      MenuItem(MenuItem *next,const char *title);

      void propose();

      // optional API 

      virtual void start() { _state=STARTED; }
      virtual bool onActionButton() { return false; }
      virtual void finish() {}
      virtual void cancel() {}
      virtual void run() {}
      virtual void onEncoder(int8_t /* direction */) {}
  
      MenuItem *getNext() const;
      bool isStarted() const;
  };


  /*
   * Constructor
   */
   
  inline MenuItem::MenuItem(MenuItem *next,const char *title)
    : _state(NONE),
      _title(title),
      _next(next) {
  }


  /*
   * propose to start this item
   */

  inline void MenuItem::propose() {

    _state=PROPOSED;

    Max7221::displayText(Max7221::Display::UPPER,_title);
    Max7221::clearDisplay(Max7221::Display::LOWER);
  }


  /*
   * Get the next item
   */

  inline MenuItem *MenuItem::getNext() const {
    return _next;
  }


  /*
   * true if started, false if proposed
   */

  inline bool MenuItem::isStarted() const {
    return _state==State::STARTED;
  }
}
