#ifndef INCLUDE_TRAFFICLIGHTSTATEPATTERNTEST_H_
#define INCLUDE_TRAFFICLIGHTSTATEPATTERNTEST_H_

#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightTestFixture.h"
#include <TCS/TrafficLightStatePattern.hpp>

class TrafficLightStatePatternSUT : public TCS::TrafficLightStatePattern {
public:
  using Timer = SimplePeriodicTimer::PeriodicTimer<TrafficLightStatePatternSUT>;
  TrafficLightStatePatternSUT(Lamp & /* red */, Lamp & /* yellow */,
                              Lamp & /* green */, Timer & /*  timer */)
      : TCS::TrafficLightStatePattern() {}
};

using StatePatternPairSUTandPolicy =
    std::pair<TrafficLightStatePatternSUT, TrafficLightMiddleEuropeTestPolicy>;

class TrafficLightStatePatternTest
    : public TrafficLightTestFixture<StatePatternPairSUTandPolicy> {
protected:
  using this_type = TrafficLightStatePatternTest;
  using base_type = TrafficLightTestFixture<StatePatternPairSUTandPolicy>;

public:
  static cute::suite make_suite() {
    return base_type::template make_suite<this_type>();
  }
};

#endif /* INCLUDE_TRAFFICLIGHTSTATEPATTERNTEST_H_ */
