
#include "../include/TrafficLightReference.hpp"
#include "TrafficLightMiddleEuropeTestFixture.h"

template <>
std::unique_ptr<SUT>
createSUT(MockLamp &red, MockLamp &yellow, MockLamp &green,
          MockPeriodicTimer<TrafficLightReference> &timer) {
  return std::unique_ptr<SUT>(
      new TrafficLightReference(red, yellow, green, timer));
}

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightReferenceTest,
                               TrafficLightMiddleEuropeTestFixture,
                               TrafficLightReference);
