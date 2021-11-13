#ifndef INCLUDE_TRAFFICLIGHTSWITCHEDTEST_H_
#define INCLUDE_TRAFFICLIGHTSWITCHEDTEST_H_

#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"
#include <TCS/TrafficLight.hpp>

using SwitchedPairSUTandPolicy =
    std::pair<TCS::TrafficLight, TrafficLightMiddleEuropeTestPolicy>;

class TrafficLightSwitchedTest
    : public TrafficLightTestFixture<SwitchedPairSUTandPolicy> {
protected:
  using this_type = TrafficLightSwitchedTest;
  using base_type = TrafficLightTestFixture<SwitchedPairSUTandPolicy>;

public:
  static cute::suite make_suite() {
    return base_type::template make_suite<this_type>();
  }
};

#endif /* INCLUDE_TRAFFICLIGHTSWITCHEDTEST_H_ */
