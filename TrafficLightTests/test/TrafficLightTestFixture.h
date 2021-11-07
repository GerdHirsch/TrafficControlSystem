#ifndef INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_
#define INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_

#include "MockLamp.hpp"
#include "MockPeriodicTimer.hpp"
#include <CrossRoad/ProtocolViolationException.hpp>
#include <CrossRoad/TrafficLight.hpp>
#include <Mock/ResultManager.hpp>
#include <gmock/gmock.h>
#include <memory>

namespace CR = CrossRoadLib;
using namespace ::testing;
using SUT = CR::TrafficLight;

// Factory method for SUTs
template <class SUTImplementation>
std::unique_ptr<SUT> createSUT(MockLamp &red, MockLamp &yellow, MockLamp &green,
                               MockPeriodicTimer<SUTImplementation> &timer);

template <class SUTImplementation>
// requires TrafficLightLike<SUTImplementation>
class TrafficLightTestFixture : public Test {
public:
  TrafficLightTestFixture()
      : rm(), red("r", rm), yellow("y", rm), green("g", rm), timer(rm){};

protected:
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
  using Timer = MockPeriodicTimer<SUTImplementation>;
  Mock::ResultManager rm;
  MockLamp red;
  MockLamp yellow;
  MockLamp green;
  Timer timer;
};

TYPED_TEST_SUITE_P(TrafficLightTestFixture);

TYPED_TEST_P(TrafficLightTestFixture, testConstructor) {

  this->rm.beginInit();
  this->initConstructor();
  this->rm.endInit();

  this->rm.beginTest();
  createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_off) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initOff_off();
  this->rm.endInit();

  this->rm.beginTest();
  sut->off();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_timerTick) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initOff_timerTick();
  this->rm.endInit();

  sut->flash();
  this->timer.tick();
  sut->off();

  this->rm.beginTest();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
  ASSERT_FALSE(this->timer.hasReceiver()) << "timer not inactive";
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_flash_6_ticks) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initOff_flash_6_ticks();
  this->rm.endInit();

  this->rm.beginTest();
  sut->flash();
  // ASSERT_TRUE(this->timer.hasReceiver()) << "hasReceiver";
  // ASSERT_TRUE(this->timer.hasCallback()) << "hasCallback";

  for (int i = 0; i < 6; ++i)
    this->timer.tick();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_off) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initFlashing_off();
  this->rm.endInit();

  sut->flash();
  this->timer.tick();

  this->rm.beginTest();
  sut->off();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_flash) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initFlashing_flash();
  this->rm.endInit();

  sut->flash();

  this->rm.beginTest();
  sut->flash();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_switchOver) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initFlashing_switchOver();
  this->rm.endInit();

  sut->flash();

  this->rm.beginTest();
  sut->switchOver();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testOperation_flash_5_ticks) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initOperation_flash_5_ticks();
  this->rm.endInit();

  sut->flash();
  sut->switchOver(); // yellow

  this->rm.beginTest();
  sut->flash();
  for (int i = 0; i < 5; ++i)
    this->timer.tick();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testYellow_5_times_switchOver) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initYellow_5_times_switchOver();
  this->rm.endInit();

  sut->flash();
  sut->switchOver(); // yellow

  this->rm.beginTest();
  sut->switchOver(); // red
  sut->switchOver();
  sut->switchOver();
  sut->switchOver();
  sut->switchOver(); // red
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
}

TYPED_TEST_P(TrafficLightTestFixture, testOperation_timerTick) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  this->rm.beginInit();
  this->initOperation_timerTick();
  this->rm.endInit();

  sut->flash();
  this->timer.tick();
  sut->switchOver(); // yellow

  this->rm.beginTest();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_THAT(this->rm.getResult(), Eq(this->rm.getExpected()));
  ASSERT_FALSE(this->timer.hasReceiver()) << "timer not inactive";
}

TYPED_TEST_P(TrafficLightTestFixture, testExceptionOperation_off) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  sut->flash();
  sut->switchOver(); // yellow
  EXPECT_THROW(sut->off(), ProtocolViolationException);
}

TYPED_TEST_P(TrafficLightTestFixture, testExceptionOff_switchOver) {
  auto sut =
      createSUT<TypeParam>(this->red, this->yellow, this->green, this->timer);

  EXPECT_THROW(sut->switchOver(), ProtocolViolationException);
}

REGISTER_TYPED_TEST_SUITE_P(TrafficLightTestFixture, testConstructor,
                            testOff_off, testOff_timerTick,
                            testOff_flash_6_ticks, testFlashing_off,
                            testFlashing_flash, testFlashing_switchOver,
                            testOperation_flash_5_ticks,
                            testYellow_5_times_switchOver,
                            testOperation_timerTick, testExceptionOperation_off,
                            testExceptionOff_switchOver);

#endif //  INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_
