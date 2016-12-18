/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

 #include "Application.h"


/*
 * Main entry point
 */

int main() {

  // interrupts off

  cli();

  // declare the program class

  nxa66::Program p;
  p.run(); 
 
  // not reached

  return 0;
}
