/*
 * TrafficLightReferenceTest.h
 *
 *  Created on: 12.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTREFERENCETEST_H_
#define INCLUDE_TRAFFICLIGHTREFERENCETEST_H_

#include "TrafficLightMiddleEuropeTest.h"
#include "TrafficLightReference.hpp"

class TrafficLightReferenceTest
    : public TrafficLightMiddleEuropeTest<TrafficLightReference> {
public:
protected:
  using this_type = TrafficLightReferenceTest;
  using base_type = TrafficLightMiddleEuropeTest<TrafficLightReference>;

  std::unique_ptr<SUT> createSUT() {
    return std::unique_ptr<SUT>(
        new TrafficLightReference(red, yellow, green, timer));
  }

public:
  static cute::suite make_suite() {
    return base_type::template make_suite<this_type>();
  }
};

#endif /* INCLUDE_TRAFFICLIGHTREFERENCETEST_H_ */
