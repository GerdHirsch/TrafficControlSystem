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
    InSequence seq;
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(yellow, off());
  }
  void initFlashing_off() override { allOff(); }
  void initFlashing_flash() override { ; }
  void initFlashing_switchOver() override {
    InSequence seq;
    EXPECT_CALL(red, off());
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(green, off());
  }
  void initOperation_flash_5_ticks() override {
    allOff();
    InSequence seq;
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(yellow, on());
  }
  void initYellow_5_times_switchOver() override { /*5 times switchOver */
    InSequence seq;
    EXPECT_CALL(red, on());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(green, off());
    EXPECT_CALL(red, on());
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(green, off());
    EXPECT_CALL(red, off());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(green, on());
    EXPECT_CALL(red, off());
    EXPECT_CALL(yellow, on());
    EXPECT_CALL(green, off());
    EXPECT_CALL(red, on());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(green, off());
  }
  void initOperation_timerTick() override {}
  void initExceptionOff_switchOver() override {}
  void initExceptionOperation_off() override {}

private:
  void allOff() {
    EXPECT_CALL(red, off());
    EXPECT_CALL(yellow, off());
    EXPECT_CALL(green, off());
  }
};

#endif /* INCLUDE_TRAFFICLIGHTMIDDLEEUROPETESTPOLICY_H_ */
