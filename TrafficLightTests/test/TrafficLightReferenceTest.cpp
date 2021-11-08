
#include "../include/TrafficLightReference.hpp"
#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"

template <>
std::unique_ptr<SUT>
createSUT(MockLamp &red, MockLamp &yellow, MockLamp &green,
          MockPeriodicTimer<TrafficLightReference> &timer) {
  return std::unique_ptr<SUT>(
      new TrafficLightReference(red, yellow, green, timer));
}
template <>
std::unique_ptr<TrafficLightTestPolicy>
createPolicy<TrafficLightReference>(MockLamp &red, MockLamp &yellow,
                                    MockLamp &green) {
  return std::unique_ptr<TrafficLightTestPolicy>(
      new TrafficLightMiddleEuropeTestPolicy(red, yellow, green));
}

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightReferenceTest,
                               TrafficLightTestFixture, TrafficLightReference);
