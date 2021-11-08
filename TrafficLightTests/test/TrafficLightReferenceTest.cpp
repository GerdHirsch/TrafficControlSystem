
#include "../include/TrafficLightReference.hpp"
#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"

template <> struct TestPolicyLookup<TrafficLightReference> {
  using PolicyType = TrafficLightMiddleEuropeTestPolicy;
};

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightReferenceTest,
                               TrafficLightTestFixture, TrafficLightReference);
