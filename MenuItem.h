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
      MenuItem *_next;

    public:
      MenuItem(MenuItem *next);

      // optional API 

      virtual void start() {}
      virtual void finish() {}
      virtual void cancel() {}
      virtual void onEncoder(int8_t direction) {}
  };
}
