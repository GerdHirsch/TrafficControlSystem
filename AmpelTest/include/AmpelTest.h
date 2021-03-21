/*
 * AmpelTest.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_AMPELTEST_H_
#define INCLUDE_AMPELTEST_H_

//#include "ResultManager.h"
#include "MockLamp.h"
#include <TCS/Lamp.h>

#include <Mock/ResultManager.hpp>

#include <CrossRoad/TrafficLight.hpp>

#include <cute.h>

#include <memory>

namespace CR = CrossRoadLib;

class AmpelTest {
public:
	AmpelTest(): rm(), red("r", rm), yellow("y", rm), green("g", rm)
	{ };
	virtual ~AmpelTest(){};
	// tests
	void testBlinkend_aus();
	virtual void initBlinkend_aus() = 0;

	// Types
	using SUT = CR::TrafficLight;
protected:
	virtual SUT& createSUT() = 0;
	Lamp& getRed()		{ return red; }
	Lamp& getYellow()	{ return yellow; }
	Lamp& getGreen()	{ return green; }

protected:
	Mock::ResultManager rm;
	MockLamp red;
	MockLamp yellow;
	MockLamp green;

public:

	template<class DerivedTest>
	static cute::suite make_suite(){
		cute::suite s {};

		s.push_back(CUTE_SMEMFUN(DerivedTest, testBlinkend_aus));

		return s;
	}
};

#endif /* INCLUDE_AMPELTEST_H_ */
