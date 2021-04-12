/*
 * TrafficLightStatePatternTest.hpp
 *
 *  Created on: 12.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTSTATEPATTERNTEST_H_
#define INCLUDE_TRAFFICLIGHTSTATEPATTERNTEST_H_

#include <TCS/TrafficLightStatePattern.hpp>
#include "TrafficLightMiddleEuropeTest.h"


class TrafficLightStatePatternTest : public TrafficLightMiddleEuropeTest<TCS::TrafficLightStatePattern> {
public:
	using this_type = TrafficLightStatePatternTest;
	using base_type = TrafficLightMiddleEuropeTest<TCS::TrafficLightStatePattern>;

protected:
	std::unique_ptr<SUT> createSUT() {
		return std::unique_ptr<SUT>(
				new TCS::TrafficLightStatePattern()
		);
	}
public:
	static cute::suite make_suite(){
		return base_type::template make_suite<this_type>();
	}
};



#endif /* INCLUDE_TRAFFICLIGHTSTATEPATTERNTEST_H_ */
