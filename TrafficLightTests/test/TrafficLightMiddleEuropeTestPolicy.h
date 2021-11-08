#ifndef INCLUDE_TRAFFICLIGHTMIDDLEEUROPETESTPOLICY_H_
#define INCLUDE_TRAFFICLIGHTMIDDLEEUROPETESTPOLICY_H_

#include "TrafficLightTestFixture.h"
#include <gmock/gmock.h>

using namespace ::testing;

class TrafficLightMiddleEuropeTestPolicy : public TrafficLightTestPolicy {
public:
  TrafficLightMiddleEuropeTestPolicy(MockLamp &red_, MockLamp &yellow_,
                                     MockLamp &green_)
      : TrafficLightTestPolicy(red_, yellow_, green_) {}

  void initConstructor() override { allOff(); }
  void initOff_off() override { ; }
  void initOff_timerTick() override { ; }
  void initOff_flash_6_ticks() override {
    allOff();
    yellow.on();
    yellow.off();
    yellow.on();
    yellow.off();
    yellow.on();
    yellow.off();
  }
  void initFlashing_off() override { allOff(); }
  void initFlashing_flash() override { ; }
  void initFlashing_switchOver() override {
    red.off();
    yellow.on();
    green.off();
  }
  void initOperation_flash_5_ticks() override {
    allOff();
    yellow.on();
    yellow.off();
    yellow.on();
    yellow.off();
    yellow.on();
  }
  void initYellow_5_times_switchOver() override { /*5 times switchOver */
    red.on();
    yellow.off();
    green.off();
    red.on();
    yellow.on();
    green.off();
    red.off();
    yellow.off();
    green.on();
    red.off();
    yellow.on();
    green.off();
    red.on();
    yellow.off();
    green.off();
  }
  void initOperation_timerTick() override {}
  void initExceptionOff_switchOver() override {}
  void initExceptionOperation_off() override {}

private:
  void allOff() {
    red.off();
    yellow.off();
    green.off();
  }
};

#endif /* INCLUDE_TRAFFICLIGHTMIDDLEEUROPETESTPOLICY_H_ */
