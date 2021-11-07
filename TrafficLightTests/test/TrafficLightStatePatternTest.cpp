#include "TrafficLightMiddleEuropeTestFixture.h"
#include <TCS/TrafficLightStatePattern.hpp>

template <>
std::unique_ptr<SUT>
createSUT(MockLamp & /* red */, MockLamp & /* yellow */, MockLamp & /* green */,
          MockPeriodicTimer<TCS::TrafficLightStatePattern> & /* timer */) {
  return std::unique_ptr<SUT>(new TCS::TrafficLightStatePattern());
}

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightStatePatternTest,
                               TrafficLightMiddleEuropeTestFixture,
                               TCS::TrafficLightStatePattern);
