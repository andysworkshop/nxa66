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
      bool _pendingPinState;
      uint32_t _pressTime;

    public:
      Switch();

      bool run();
      bool getState() const;
  };


  /*
   * Constructor
   */

  template<class TGpio>
  inline Switch<TGpio>::Switch() {
    _pinState=TGpio::read();
    _state=IDLE;
  }


  /*
   * Get current state
   */

  template<class TGpio>
  inline bool Switch<TGpio>::getState() const {
    return _pinState;
  }


  /*
   * Main loop
   */

  template<class TGpio>
  inline bool Switch<TGpio>::run() {

    bool newState=TGpio::read();

    switch(_state) {

      case IDLE:
        if(newState!=_pinState) {
          _pendingPinState=newState;
          _state=WAITING;
          _pressTime=MillisecondTimer::millis();
        }
        return false;

      case WAITING:
        if(MillisecondTimer::difference(_pressTime)>20) {
     
          _state=IDLE;
          _pinState=newState;
     
          return newState==_pendingPinState;
        }
        return false;

      default:
        return false;
    }
  }
}
