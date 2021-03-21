/*
 * AmpelTest.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef INCLUDE_TRAFFICLIGHTTEST_H_
#define INCLUDE_TRAFFICLIGHTTEST_H_

#include "../Mocks/MockPeriodicTimer.hpp"
#include "../Mocks/MockLamp.hpp"

#include <Mock/ResultManager.hpp>

#include <CrossRoad/TrafficLight.hpp>

#include <cute.h>

#include <iostream>
#include <memory>

namespace CR = CrossRoadLib;

class TrafficLightTest {
public:
	TrafficLightTest(): rm(), red("r", rm), yellow("y", rm), green("g", rm)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	};
	virtual ~TrafficLightTest(){};
	// tests
	void testConstructor();
	virtual void initConstructor() = 0;
	void testFlashing_off();
	virtual void initFlashing_off() = 0;

	// Types
	using SUT = CR::TrafficLight;
protected:
	virtual std::unique_ptr<SUT> createSUT() = 0;

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

		s.push_back(CUTE_SMEMFUN(DerivedTest, testConstructor));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_off));

		return s;
	}
};

#endif /* INCLUDE_TRAFFICLIGHTTEST_H_ */
