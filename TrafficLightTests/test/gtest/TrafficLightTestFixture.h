#ifndef INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_
#define INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_

#include "Mocks/GMockPeriodicTimer.hpp"
#include "TrafficLightTestPolicy.h"
#include <CrossRoad/ProtocolViolationException.hpp>
#include <CrossRoad/TrafficLight.hpp>
#include <gmock/gmock.h>
#include <memory>
#include <utility>

namespace gt = ::testing;

template <class PairSUTandPolicy>
// requires std::pair<TrafficLightLike, TrafficLightTestPolicyLike>
class TrafficLightTestFixture : public gt::Test {
public:
  using SUTImpl = typename PairSUTandPolicy::first_type;
  using PolicyImpl = typename PairSUTandPolicy::second_type;
  using SUT = CrossRoadLib::TrafficLight;

  TrafficLightTestFixture() : expectation{createPolicy()} {};

protected:
  void SetUp() override {
    red = gt::NiceMock<GMockLamp>(red);
    yellow = gt::NiceMock<GMockLamp>(yellow);
    green = gt::NiceMock<GMockLamp>(green);
  }

  void SetUpEnd() {
    red = gt::StrictMock<GMockLamp>(red);
    yellow = gt::StrictMock<GMockLamp>(yellow);
    green = gt::StrictMock<GMockLamp>(green);
  }

  std::unique_ptr<SUT> createSUT() {
    return std::make_unique<SUTImpl>(red, yellow, green, timer);
  }

  std::unique_ptr<TrafficLightTestPolicy> createPolicy() {
    return std::make_unique<PolicyImpl>(red, yellow, green);
  }

  using Timer = GMockPeriodicTimer<SUTImpl>;
  GMockLamp red{};
  GMockLamp yellow{};
  GMockLamp green{};
  gt::StrictMock<Timer> timer{};
  std::unique_ptr<TrafficLightTestPolicy> expectation;
};

TYPED_TEST_SUITE_P(TrafficLightTestFixture);

TYPED_TEST_P(TrafficLightTestFixture, testConstructor) {
  this->SetUpEnd();

  this->expectation->initConstructor();

  this->createSUT();
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_off) {
  auto sut = this->createSUT();
  this->SetUpEnd();

  this->expectation->initOff_off();

  sut->off();
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_timerTick) {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  sut->off();
  this->SetUpEnd();

  this->expectation->initOff_timerTick();

  this->timer.tick();

  ASSERT_FALSE(this->timer.hasReceiver()) << "timer not inactive";
}

TYPED_TEST_P(TrafficLightTestFixture, testOff_flash_6_ticks) {
  auto sut = this->createSUT();
  this->SetUpEnd();

  this->expectation->initOff_flash_6_ticks();

  sut->flash();

  for (int i = 0; i < 6; ++i)
    this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_off) {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  this->SetUpEnd();

  this->expectation->initFlashing_off();

  sut->off();
  this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_flash) {
  auto sut = this->createSUT();
  sut->flash();
  this->SetUpEnd();

  this->expectation->initFlashing_flash();

  sut->flash();
}

TYPED_TEST_P(TrafficLightTestFixture, testFlashing_switchOver) {
  auto sut = this->createSUT();
  sut->flash();
  this->SetUpEnd();

  this->expectation->initFlashing_switchOver();

  sut->switchOver();
  this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testOperation_flash_5_ticks) {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  this->SetUpEnd();

  this->expectation->initOperation_flash_5_ticks();

  sut->flash();
  for (int i = 0; i < 5; ++i)
    this->timer.tick();
}

TYPED_TEST_P(TrafficLightTestFixture, testYellow_5_times_switchOver) {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  this->SetUpEnd();

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
  this->SetUpEnd();

  this->expectation->initOperation_timerTick();

  this->timer.tick();

  ASSERT_FALSE(this->timer.hasReceiver()) << "timer not inactive";
}

TYPED_TEST_P(TrafficLightTestFixture, testExceptionOperation_off) {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  this->SetUpEnd();

  EXPECT_THROW(sut->off(), ProtocolViolationException);
}

TYPED_TEST_P(TrafficLightTestFixture, testExceptionOff_switchOver) {
  auto sut = this->createSUT();
  this->SetUpEnd();

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
