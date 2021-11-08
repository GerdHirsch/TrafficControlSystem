#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"
#include <TCS/TrafficLightStatePattern.hpp>

template <>
std::unique_ptr<SUT>
createSUT(MockLamp & /* red */, MockLamp & /* yellow */, MockLamp & /* green */,
          MockPeriodicTimer<TCS::TrafficLightStatePattern> & /* timer */) {
  return std::unique_ptr<SUT>(new TCS::TrafficLightStatePattern());
}
template <>
std::unique_ptr<TrafficLightTestPolicy>
createPolicy<TCS::TrafficLightStatePattern>(MockLamp &red, MockLamp &yellow,
                                            MockLamp &green) {
  return std::unique_ptr<TrafficLightTestPolicy>(
      new TrafficLightMiddleEuropeTestPolicy(red, yellow, green));
}
INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightStatePatternTest,
                               TrafficLightTestFixture,
                               TCS::TrafficLightStatePattern);
