#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"
#include <TCS/TrafficLight.hpp>

template <> struct TestPolicyLookup<TCS::TrafficLight> {
  using PolicyType = TrafficLightMiddleEuropeTestPolicy;
};

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightSwitchedTest,
                               TrafficLightTestFixture, TCS::TrafficLight);
