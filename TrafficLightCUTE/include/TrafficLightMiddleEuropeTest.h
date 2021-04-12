/*
 * AmpelReferenceTest.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTMIDDLEEUROPETEST_H_
#define INCLUDE_TRAFFICLIGHTMIDDLEEUROPETEST_H_

#include "TrafficLightReference.hpp"

#include "TrafficLightTest.h"

template<class SUTImplementation_ = TrafficLightReference>
class TrafficLightMiddleEuropeTest : public TrafficLightTest<SUTImplementation_>
{
public:
	using SUTImplementation = SUTImplementation_;
	using this_type = TrafficLightMiddleEuropeTest<SUTImplementation>;
	using base_type = TrafficLightTest<SUTImplementation>;
	using SUT = typename base_type::SUT;
	using base_type::red;
	using base_type::yellow;
	using base_type::green;
	using base_type::timer;

	TrafficLightMiddleEuropeTest()
	{
//		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
protected:

	// init tests
	void initConstructor() 	{ allOff();	}
	void initOff_off(){ ; }
	void initOff_timerTick(){ ; }
	void initOff_flash_6_ticks() {
		allOff();
		yellow.on(); yellow.off(); yellow.on();  yellow.off(); yellow.on();  yellow.off();
	}
	void initFlashing_off() { allOff();	}
	void initFlashing_flash(){ ; }
	void initFlashing_switchOver(){ red.off(); yellow.on(); green.off();}
	void initOperation_flash_5_ticks() {
		allOff();
		yellow.on(); yellow.off(); yellow.on();  yellow.off(); yellow.on();
	}
	void initYellow_5_times_switchOver(){ /*5 times switchOver */
		red.on(); yellow.off(); green.off();
		red.on(); yellow.on(); green.off();
		red.off(); yellow.off(); green.on();
		red.off(); yellow.on(); green.off();
		red.on(); yellow.off(); green.off();
	}
	void initOperation_timerTick(){}
	void initExceptionOff_switchOver(){}
	void initExceptionOperation_off(){}



	// helper
	void allOff(){ red.off(); yellow.off(); green.off();}
private:

};

#endif /* INCLUDE_TRAFFICLIGHTMIDDLEEUROPETEST_H_ */
