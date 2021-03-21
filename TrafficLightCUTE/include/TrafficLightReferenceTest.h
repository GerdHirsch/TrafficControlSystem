/*
 * AmpelReferenceTest.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTREFERENCETEST_H_
#define INCLUDE_TRAFFICLIGHTREFERENCETEST_H_

#include "TrafficLightReference.hpp"

#include "TrafficLightTest.h"

class TrafficLightReferenceTest : public TrafficLightTest
{
public:
	using this_type = TrafficLightReferenceTest;
	using base_type = TrafficLightTest;

	TrafficLightReferenceTest()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}
protected:
	std::unique_ptr<SUT> createSUT() {
		return std::unique_ptr<SUT>(new TrafficLightReference(getRed(), getYellow(), getGreen()));
	}

	void initConstructor() { red.off(); yellow.off(); green.off();	}
	void initFlashing_off() { red.off(); yellow.off(); green.off();	}
private:
};



#endif /* INCLUDE_TRAFFICLIGHTREFERENCETEST_H_ */
