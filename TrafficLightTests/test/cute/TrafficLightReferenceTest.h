#ifndef INCLUDE_TRAFFICLIGHTREFERENCETEST_H_
#define INCLUDE_TRAFFICLIGHTREFERENCETEST_H_

#include "TrafficLightMiddleEuropeTestPolicy.h"
#include "TrafficLightReference.hpp"
#include "TrafficLightTestFixture.h"

using ReferencePairSUTandPolicy =
    std::pair<TrafficLightReference, TrafficLightMiddleEuropeTestPolicy>;

class TrafficLightReferenceTest
    : public TrafficLightTestFixture<ReferencePairSUTandPolicy> {
protected:
  using this_type = TrafficLightReferenceTest;
  using base_type = TrafficLightTestFixture<ReferencePairSUTandPolicy>;

public:
  static cute::suite make_suite() {
    return base_type::template make_suite<this_type>();
  }
};

#endif /* INCLUDE_TRAFFICLIGHTREFERENCETEST_H_ */
