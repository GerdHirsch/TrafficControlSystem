/*
 * TrafficLightTest.h
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
template<class SUTImplementation>
class TrafficLightTest {
public:
	TrafficLightTest(): rm(), red("r", rm), yellow("y", rm), green("g", rm), timer(rm)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	};
	virtual ~TrafficLightTest(){};
	// tests
	void testConstructor();
	virtual void initConstructor() = 0;
	void testOff_flash();
	virtual void initOff_flash() = 0;
	void testFlashing_off();
	virtual void initFlashing_off() = 0;

	// Types
	using SUT = CR::TrafficLight;
	using Timer = MockPeriodicTimer<SUTImplementation>;
protected:
	virtual std::unique_ptr<SUT> createSUT() = 0;

	Lamp& getRed()		{ return red; }
	Lamp& getYellow()	{ return yellow; }
	Lamp& getGreen()	{ return green; }
	Timer& getTimer() 	{ return timer; }
	SUT& getSUT(){
		if(!pSUT)
			pSUT = createSUT();
		return *pSUT;
	}

protected:
	Mock::ResultManager rm;
	MockLamp red;
	MockLamp yellow;
	MockLamp green;
	Timer timer;
	std::unique_ptr<SUT> pSUT;
public:

	template<class DerivedTest>
	static cute::suite make_suite(){
		cute::suite s {};

		s.push_back(CUTE_SMEMFUN(DerivedTest, testConstructor));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_flash));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_off));

		return s;
	}
};

template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testConstructor(){

	rm.beginInit();
	initConstructor();
	rm.endInit();


	rm.beginTest();
	createSUT();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
//	ASSERT_EQUAL(true, rm.success());
}
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testOff_flash(){
	auto sut = createSUT();

	rm.beginInit();
	initOff_flash();
	rm.endInit();

	rm.beginTest();
	sut->flash();
	ASSERTM("hasReceiver", timer.hasReceiver());
	ASSERTM("hasCallback", timer.hasCallback());

	for(int i=0; i<6; ++i)
		timer.tick();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testFlashing_off(){
	auto sut = createSUT();

	rm.beginInit();
	initFlashing_off();
	rm.endInit();

	sut->flash();

	rm.beginTest();
	sut->off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}

#endif /* INCLUDE_TRAFFICLIGHTTEST_H_ */
