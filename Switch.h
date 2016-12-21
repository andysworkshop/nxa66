/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */


namespace nxa66 {


  /*
   * Base classes for switches
   */

  template<class TGpio> 
  class Switch {

    protected:
      enum {
        IDLE,
        WAITING
      } _state;

      bool _pinState;

    public:
      Switch();

      void onSwitchInterrupt();
      bool getState() const;
  };


  /*
   * Constructor
   */

  template<class TGpio>
  inline Switch<TGpio>::Switch() {
    _currentState=TGpio::read();
  }


  /*
   * Get current state
   */

  template<class TGpio>
  inline bool Switch<TGpio>::getState() const {
    return _pinState;
  }


  /*
   * Handle the switch interrupt
   */

  template<class TGpio>
  inline void Switch<TGpio>::onSwitchInterrupt() {

    // do nothing if in the debounce period

    if(_state==WAITING)
      return;

    // do nothing if our state has not proposed a change

    bool newPinState=TGpio::read();
    if(newPinState==_pinState)
      return;

    // start the wait timer

    _state=WAITING;
  }
}
