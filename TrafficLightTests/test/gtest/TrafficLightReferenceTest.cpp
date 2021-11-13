#include "TrafficLightReference.hpp"
#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"

using PairSUTandPolicy =
    std::pair<TrafficLightReference, TrafficLightMiddleEuropeTestPolicy>;

INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightReferenceTest,
                               TrafficLightTestFixture, PairSUTandPolicy);
