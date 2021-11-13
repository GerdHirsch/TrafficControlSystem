#ifndef INCLUDE_TRAFFICLIGHTTESTPOLICY_H_
#define INCLUDE_TRAFFICLIGHTTESTPOLICY_H_

#include "Mocks/GMockLamp.hpp"

class TrafficLightTestPolicy {
public:
  TrafficLightTestPolicy(GMockLamp &red_, GMockLamp &yellow_, GMockLamp &green_)
      : red(red_), yellow(yellow_), green(green_){};
  virtual void initConstructor() = 0;
  virtual void initOff_off() = 0;
  virtual void initOff_timerTick() = 0;
  virtual void initOff_flash_6_ticks() = 0;
  virtual void initFlashing_off() = 0;
  virtual void initFlashing_flash() = 0;
  virtual void initFlashing_switchOver() = 0;
  virtual void initOperation_flash_5_ticks() = 0;
  virtual void initYellow_5_times_switchOver() = 0;
  virtual void initOperation_timerTick() = 0;
  virtual void initExceptionOff_switchOver() = 0;
  virtual void initExceptionOperation_off() = 0;

protected:
  GMockLamp &red;
  GMockLamp &yellow;
  GMockLamp &green;
};

#endif //  INCLUDE_TRAFFICLIGHTTESTPOLICY_H_
