/*
 * TrafficLightSwitchedTest.h
 *
 *  Created on: 12.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTSWITCHEDTEST_H_
#define INCLUDE_TRAFFICLIGHTSWITCHEDTEST_H_

#include "TrafficLightMiddleEuropeTest.h"
#include <TCS/TrafficLight.hpp>

class TrafficLightSwitchedTest : public TrafficLightMiddleEuropeTest<TCS::TrafficLight>{
public:

protected:
	using this_type = TrafficLightSwitchedTest;
	using base_type = TrafficLightMiddleEuropeTest<TCS::TrafficLight>;

	std::unique_ptr<SUT> createSUT() {
		return std::unique_ptr<SUT>(
				new TCS::TrafficLight(red, yellow, green, timer)
		);
	}
public:
	static cute::suite make_suite(){
		return base_type::template make_suite<this_type>();
	}
};




#endif /* INCLUDE_TRAFFICLIGHTSWITCHEDTEST_H_ */
