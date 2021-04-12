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
#include <CrossRoad/ProtocolViolationException.hpp>

#include <cute.h>

#include <iostream>
#include <memory>

namespace CR = CrossRoadLib;
template<class SUTImplementation>
class TrafficLightTest {
public:
	TrafficLightTest(): rm(), red("r", rm), yellow("y", rm), green("g", rm), timer(rm)
	{
//		std::cout << __PRETTY_FUNCTION__ << std::endl;
	};

	virtual ~TrafficLightTest(){};
	// tests
	void testConstructor();
	virtual void initConstructor() = 0;
	// Off
	void testOff_off();
	virtual void initOff_off() = 0;
	void testOff_flash_6_ticks();
	virtual void initOff_flash_6_ticks() = 0;
	// Flashing
	void testFlashing_off();
	virtual void initFlashing_off() = 0;
	void testFlashing_flash();
	virtual void initFlashing_flash() = 0;
	void testFlashing_switchOver();
	virtual void initFlashing_switchOver() = 0;
	// Operation
	void testOperation_flash_5_ticks();
	virtual void initOperation_flash_5_ticks() = 0;
	void testOperation_5_times_switchOver();
	virtual void initOperation_5_times_switchOver() = 0;
	void testOperation_timerTick();
	virtual void initOperation_timerTick() = 0;
	// Exceptions
	void testExceptionOff_switchOver();
	virtual void initExceptionOff_switchOver() = 0;
	void testExceptionOperation_off();
	virtual void initExceptionOperation_off() = 0;

	// Types
	using SUT = CR::TrafficLight;
	using Timer = MockPeriodicTimer<SUTImplementation>;
protected:
	virtual std::unique_ptr<SUT> createSUT() = 0;
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
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_off));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_flash_6_ticks));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_off));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_flash));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flash_5_ticks));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_5_times_switchOver));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_timerTick));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testExceptionOff_switchOver));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testExceptionOperation_off));

		return s;
	}
};
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testConstructor(){

	rm.beginInit();
	initConstructor();
	rm.endInit();


	rm.beginTest();
	getSUT();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
//	ASSERT_EQUAL(true, rm.success());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testOff_off(){
	auto &sut = getSUT();

	rm.beginInit();
	initOff_off();
	rm.endInit();

	rm.beginTest();
	sut.off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testOff_flash_6_ticks(){
	auto &sut = getSUT();

	rm.beginInit();
	initOff_flash_6_ticks();
	rm.endInit();

	rm.beginTest();
	sut.flash();
//	ASSERTM("hasReceiver", timer.hasReceiver());
//	ASSERTM("hasCallback", timer.hasCallback());

	for(int i=0; i<6; ++i)
		timer.tick();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testFlashing_off(){
	auto &sut = getSUT();

	rm.beginInit();
	initFlashing_off();
	rm.endInit();

	sut.flash();
	timer.tick();

	rm.beginTest();
	sut.off();
	timer.tick();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testFlashing_flash(){
	auto &sut = getSUT();

	rm.beginInit();
	initFlashing_flash();
	rm.endInit();

	sut.flash();

	rm.beginTest();
	sut.flash();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testOperation_flash_5_ticks(){
	auto &sut = getSUT();

	rm.beginInit();
	initOperation_flash_5_ticks();
	rm.endInit();

	sut.flash();
	sut.switchOver(); // yellow

	rm.beginTest();
	sut.flash();
	for(int i=0; i<5; ++i)
		timer.tick();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testOperation_5_times_switchOver(){
	auto &sut = getSUT();

	rm.beginInit();
	initOperation_5_times_switchOver();
	rm.endInit();

	sut.flash();
	sut.switchOver();//yellow

	rm.beginTest();
	sut.switchOver();//red
	sut.switchOver();
	sut.switchOver();
	sut.switchOver();
	sut.switchOver();//red
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testOperation_timerTick(){
	auto &sut = getSUT();

	rm.beginInit();
	initOperation_timerTick();
	rm.endInit();

	sut.flash();
	timer.tick();
	sut.switchOver();//yellow

	rm.beginTest();
	timer.tick();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
	ASSERTM("timer not inactive", !timer.hasReceiver());
}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testExceptionOperation_off(){
	auto &sut = getSUT();

	sut.flash();
	sut.switchOver();//yellow
	ASSERT_THROWS(sut.off(), ProtocolViolationException);

}
//--------------------------
template<class SUTImpl>
inline
void TrafficLightTest<SUTImpl>::testExceptionOff_switchOver(){
	auto &sut = getSUT();

	ASSERT_THROWS(sut.switchOver(), ProtocolViolationException);
}

#endif /* INCLUDE_TRAFFICLIGHTTEST_H_ */
