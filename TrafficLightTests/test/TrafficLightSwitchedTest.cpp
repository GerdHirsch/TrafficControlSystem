#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"
#include <TCS/TrafficLight.hpp>

template <>
std::unique_ptr<SUT> createSUT(MockLamp &red, MockLamp &yellow, MockLamp &green,
                               MockPeriodicTimer<TCS::TrafficLight> &timer) {
  return std::unique_ptr<SUT>(new TCS::TrafficLight(red, yellow, green, timer));
}
template <>
std::unique_ptr<TrafficLightTestPolicy>
createPolicy<TCS::TrafficLight>(MockLamp &red, MockLamp &yellow,
                                MockLamp &green) {
  return std::unique_ptr<TrafficLightTestPolicy>(
      new TrafficLightMiddleEuropeTestPolicy(red, yellow, green));
}

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightSwitchedTest,
                               TrafficLightTestFixture, TCS::TrafficLight);
