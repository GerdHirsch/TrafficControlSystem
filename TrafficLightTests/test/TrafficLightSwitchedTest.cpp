#include "TrafficLightMiddleEuropeTestFixture.h"
#include <TCS/TrafficLight.hpp>

template <>
std::unique_ptr<SUT> createSUT(MockLamp &red, MockLamp &yellow, MockLamp &green,
                               MockPeriodicTimer<TCS::TrafficLight> &timer) {
  return std::unique_ptr<SUT>(new TCS::TrafficLight(red, yellow, green, timer));
}

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightSwitchedTest,
                               TrafficLightMiddleEuropeTestFixture,
                               TCS::TrafficLight);
