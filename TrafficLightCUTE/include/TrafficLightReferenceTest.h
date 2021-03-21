/*
 * AmpelReferenceTest.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTREFERENCETEST_H_
#define INCLUDE_TRAFFICLIGHTREFERENCETEST_H_

#include "TrafficLightReference.h"

#include "TrafficLightTest.h"

class TrafficLightReferenceTest : public TrafficLightTest
{
public:
	using this_type = TrafficLightReferenceTest;
	using base_type = TrafficLightTest;

	TrafficLightReferenceTest() : referenceImplementation(red, yellow, green)
{}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}
protected:
	SUT& createSUT() {
		return referenceImplementation;
	}

	void initFlashing_off() { red.off(); yellow.off(); green.off();	}
private:
	TrafficLightReference referenceImplementation;
};



#endif /* INCLUDE_TRAFFICLIGHTREFERENCETEST_H_ */
