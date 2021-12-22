#ifndef INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_
#define INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_

#include "Mocks/MockPeriodicTimer.hpp"
#include "TrafficLightTestPolicy.h"
#include <CrossRoad/ProtocolViolationException.hpp>
#include <CrossRoad/TrafficLight.hpp>
#include <Mock/ResultManager.hpp>
#include <cute/cute.h>
#include <iostream>
#include <memory>

template <class PairSUTandPolicy>
// requires std::pair<TrafficLightLike, TrafficLightTestPolicyLike>
class TrafficLightTestFixture {
public:
  using SUTImplementation = typename PairSUTandPolicy::first_type;
  using PolicyType = typename PairSUTandPolicy::second_type;
  using SUTInterface = CrossRoadLib::TrafficLight;

  TrafficLightTestFixture()
      : rm(), red("r", rm), yellow("y", rm), green("g", rm),
        timer(rm), expectation{
                       std::make_unique<PolicyType>(red, yellow, green)} {};

  virtual ~TrafficLightTestFixture(){};

protected:
  // tests
  void testConstructor();
  // Off
  void testOff_off();
  void testOff_timerTick();
  void testOff_flash_6_ticks();
  // Flashing
  void testFlashing_off();
  void testFlashing_flash();
  void testFlashing_switchOver();
  // Operation
  void testOperation_flash_5_ticks();
  void testYellow_5_times_switchOver();
  void testOperation_timerTick();
  // Exceptions
  void testExceptionOff_switchOver();
  void testExceptionOperation_off();

  std::unique_ptr<SUTInterface> createSUT() {
    return std::make_unique<SUTImplementation>(red, yellow, green, timer);
  }

  using Timer = MockPeriodicTimer<SUTImplementation>;
  Mock::ResultManager rm;
  MockLamp red;
  MockLamp yellow;
  MockLamp green;
  Timer timer;
  std::unique_ptr<TrafficLightTestPolicy> expectation;

public:
  template <class DerivedTest> static cute::suite make_suite() {
    cute::suite s{};

    s.push_back(CUTE_SMEMFUN(DerivedTest, testConstructor));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_off));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_timerTick));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_flash_6_ticks));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_off));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_flash));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_switchOver));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flash_5_ticks));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testYellow_5_times_switchOver));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_timerTick));

    s.push_back(CUTE_SMEMFUN(DerivedTest, testExceptionOff_switchOver));
    s.push_back(CUTE_SMEMFUN(DerivedTest, testExceptionOperation_off));

    return s;
  }
};

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testConstructor() {

  this->rm.beginInit();
  this->expectation->initConstructor();
  this->rm.endInit();

  this->rm.beginTest();
  this->createSUT();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl> void TrafficLightTestFixture<SUTImpl>::testOff_off() {
  auto sut = this->createSUT();

  this->rm.beginInit();
  this->expectation->initOff_off();
  this->rm.endInit();

  this->rm.beginTest();
  sut->off();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testOff_timerTick() {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  sut->off();


  this->rm.beginInit();
  this->expectation->initOff_timerTick();
  this->rm.endInit();

  this->rm.beginTest();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
  ASSERTM("timer not inactive", !this->timer.hasReceiver());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testOff_flash_6_ticks() {
  auto sut = this->createSUT();

  this->rm.beginInit();
  this->expectation->initOff_flash_6_ticks();
  this->rm.endInit();

  this->rm.beginTest();
  sut->flash();

  for (int i = 0; i < 6; ++i)
    this->timer.tick();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testFlashing_off() {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();

  this->rm.beginInit();
  this->expectation->initFlashing_off();
  this->rm.endInit();

  this->rm.beginTest();
  sut->off();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testFlashing_flash() {
  auto sut = this->createSUT();
  sut->flash();

  this->rm.beginInit();
  this->expectation->initFlashing_flash();
  this->rm.endInit();


  this->rm.beginTest();
  sut->flash();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testFlashing_switchOver() {
  auto sut = this->createSUT();
  sut->flash();

  this->rm.beginInit();
  this->expectation->initFlashing_switchOver();
  this->rm.endInit();

  this->rm.beginTest();
  sut->switchOver();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testOperation_flash_5_ticks() {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow

  this->rm.beginInit();
  this->expectation->initOperation_flash_5_ticks();
  this->rm.endInit();

  this->rm.beginTest();
  sut->flash();
  for (int i = 0; i < 5; ++i)
    this->timer.tick();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testYellow_5_times_switchOver() {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow

  this->rm.beginInit();
  this->expectation->initYellow_5_times_switchOver();
  this->rm.endInit();

  this->rm.beginTest();
  sut->switchOver(); // red
  sut->switchOver();
  sut->switchOver();
  sut->switchOver();
  sut->switchOver(); // red
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testOperation_timerTick() {
  auto sut = this->createSUT();
  sut->flash();
  this->timer.tick();
  sut->switchOver(); // yellow

  this->rm.beginInit();
  this->expectation->initOperation_timerTick();
  this->rm.endInit();

  this->rm.beginTest();
  this->timer.tick();
  this->rm.endTest();

  ASSERT_EQUAL(this->rm.getExpected(), this->rm.getResult());
  ASSERTM("timer not inactive", !this->timer.hasReceiver());
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testExceptionOperation_off() {
  auto sut = this->createSUT();
  sut->flash();
  sut->switchOver(); // yellow
  ASSERT_THROWS(sut->off(), ProtocolViolationException);
}

template <class SUTImpl>
void TrafficLightTestFixture<SUTImpl>::testExceptionOff_switchOver() {
  auto sut = this->createSUT();

  ASSERT_THROWS(sut->switchOver(), ProtocolViolationException);
}

#endif //  INCLUDE_TRAFFICLIGHTTESTFIXTURE_H_
