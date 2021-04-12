/*
 * ReferenceTest.h
 *
 *  Created on: 12.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_REFERENCETEST_H_
#define INCLUDE_REFERENCETEST_H_

#include "TrafficLightMiddleEuropeTest.h"
#include "TrafficLightReference.hpp"

class ReferenceTest : public TrafficLightMiddleEuropeTest<TrafficLightReference>{
public:

protected:
	using this_type = ReferenceTest;
	using base_type = TrafficLightMiddleEuropeTest<TrafficLightReference>;

	std::unique_ptr<SUT> createSUT() {
		return std::unique_ptr<SUT>(
				new TrafficLightReference(red, yellow, green, timer)
		);
	}
public:
	static cute::suite make_suite(){
		return base_type::template make_suite<this_type>();
	}
};



#endif /* INCLUDE_REFERENCETEST_H_ */
