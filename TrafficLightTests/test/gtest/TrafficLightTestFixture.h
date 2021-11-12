#ifndef INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_
#define INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_

#include "Mocks/GMockLamp.hpp"
#include "Mocks/GMockPeriodicTimer.hpp"
#include <CrossRoad/ProtocolViolationException.hpp>
#include <CrossRoad/TrafficLight.hpp>
#include <gmock/gmock.h>
#include <memory>
#include <utility>

namespace gt = ::testing;

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

template <class PairSUTandPolicy>
// requires std::pair<TrafficLightLike, TrafficLightTestPolicyLike>
class TrafficLightTestFixture : public gt::Test {
public:
  using SUTImplementation = typename PairSUTandPolicy::first_type;
  using PolicyType = typename PairSUTandPolicy::second_type;
  using SUTInterface = CrossRoadLib::TrafficLight;

  TrafficLightTestFixture()
      : expectation{std::make_unique<PolicyType>(red, yellow, green)} {};

protected:
  gt::MockFunction<void()>
      endArrangeStatements; // Checkpoint for starting the test

  void SetUp() override {
    gt::ExpectationSet allowed_arrange_calls;
    allowed_arrange_calls += EXPECT_CALL(red, on).Times(gt::AnyNumber());
    allowed_arrange_calls += EXPECT_CALL(red, off).Times(gt::AnyNumber());
    allowed_arrange_calls += EXPECT_CALL(yellow, on).Times(gt::AnyNumber());
    allowed_arrange_calls += EXPECT_CALL(yellow, off).Times(gt::AnyNumber());
    allowed_arrange_calls += EXPECT_CALL(green, on).Times(gt::AnyNumber());
    allowed_arrange_calls += EXPECT_CALL(green, off).Times(gt::AnyNumber());
    allowed_arrange_calls +=
        EXPECT_CALL(timer, setIntervalDuration).Times(gt::AnyNumber());
    EXPECT_CALL(endArrangeStatements, Call()).After(allowed_arrange_calls);
  }

  void arrangeEnd() { this->endArrangeStatements.Call(); }

  std::unique_ptr<SUTInterface> createSUT() {
    return std::make_unique<SUTImplementation>(red, yellow, green, timer);
  }

  using Timer = GMockPeriodicTimer<SUTImplementation>;
  gt::StrictMock<GMockLamp> red{};
  gt::StrictMock<GMockLamp> yellow{};
  gt::StrictMock<GMockLamp> green{};
  gt::StrictMock<Timer> timer{};
  std::unique_ptr<TrafficLightTestPolicy> expectation;
};

TYPED_TEST_SUITE_P(TrafficLightTestFixture);

TYPED_TEST_P(TrafficLightTestFixture, testConstructor) {
  this->arrangeEnd();

  this->expectation->initConstructor();

  this->createSUT();
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_off) {
  auto sut = this->createSUT();
  this->arrangeEnd();

  this->expectation->initOff_off();

  sut->off();
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_timerTick) {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  sut->off();
  this->arrangeEnd();

  this->expectation->initOff_timerTick();

  this->timer.tick();

  ASSERT_FALSE(this->timer.hasReceiver()) << "timer not inactive";
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_flash_6_ticks) {
  auto sut = this->createSUT();
  this->arrangeEnd();

  this->expectation->initOff_flash_6_ticks();

  sut->flash();
  // ASSERT_TRUE(this->timer.hasReceiver()) << "hasReceiver";
  // ASSERT_TRUE(this->timer.hasCallback()) << "hasCallback";

  for (int i = 0; i < 6; ++i)
    this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_off) {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  this->arrangeEnd();

  this->expectation->initFlashing_off();

  sut->off();
  this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_flash) {
  auto sut = this->createSUT();
  sut->flash();
  this->arrangeEnd();

  this->expectation->initFlashing_flash();

  sut->flash();
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_switchOver) {
  auto sut = this->createSUT();
  sut->flash();
  this->arrangeEnd();

  this->expectation->initFlashing_switchOver();

  sut->switchOver();
  this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testOperation_flash_5_ticks) {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  this->arrangeEnd();

  this->expectation->initOperation_flash_5_ticks();

  sut->flash();
  for (int i = 0; i < 5; ++i)
    this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testYellow_5_times_switchOver) {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  this->arrangeEnd();

  this->expectation->initYellow_5_times_switchOver();

  sut->switchOver(); // red
  sut->switchOver();
  sut->switchOver();
  sut->switchOver();
  sut->switchOver(); // red
}

TYPED_TEST_P(TrafficLightTestFixture, testOperation_timerTick) {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  sut->switchOver(); // yellow
  this->arrangeEnd();

  this->expectation->initOperation_timerTick();

  this->timer.tick();

  ASSERT_FALSE(this->timer.hasReceiver()) << "timer not inactive";
}

TYPED_TEST_P(TrafficLightTestFixture, testExceptionOperation_off) {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  this->arrangeEnd();

  EXPECT_THROW(sut->off(), ProtocolViolationException);
}

TYPED_TEST_P(TrafficLightTestFixture, testExceptionOff_switchOver) {
  auto sut = this->createSUT();
  this->arrangeEnd();

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
