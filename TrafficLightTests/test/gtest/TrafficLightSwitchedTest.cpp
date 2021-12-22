#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"
#include <TCS/TrafficLight.hpp>

using PairSUTandPolicy =
    std::pair<TCS::TrafficLight, TrafficLightMiddleEuropeTestPolicy>;
INSTANTIATE_TYPED_TEST_SUITE_P(TrafficLightSwitchedTest,
                               TrafficLightTestFixture, PairSUTandPolicy);
