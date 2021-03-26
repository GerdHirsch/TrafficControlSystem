/*
 * CrossRoadStartTest.hpp
 *
 *  Created on: 26.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_CROSSROADSTARTTEST_HPP_
#define INCLUDE_CROSSROADSTARTTEST_HPP_

#include "../Mocks/MockTrafficLight.hpp"
#include "../Mocks/MockTimer.hpp"
#include "../Mocks/DurationStreamOperator.hpp"
#include "../Mocks/EnumStreamOperator.hpp"

#include <CrossRoad/CrossRoad.hpp>

#include "cute.h"

#include <memory>

namespace CR = CrossRoadLib;

class CrossRoadStartTest{
public:
	using this_type = CrossRoadStartTest;
	CrossRoadStartTest()
	:
		rm(),
		a1("a1", rm), a2("a2", rm), a3("a3", rm),
		timer(rm)
	{}
	//==============================
	// Tests
	//==============================
	void testConstuctor();
	virtual void initConstructor();

	void testOFF_off(); // ignore event
	void testOFF_flash();
	virtual void initOFF_flash();
	void testOFFMinDuration_flash_deferred();
	virtual void initOFFMinDuration_flash_deferred();

	void testFlashing_flash(); // ignore event

	void testFlashing_off();
	virtual void initFlashing_off();

	void testFlashingMinDuration_off_deferred();
	virtual void initFlashingMinDuration_off_deferred();

	void testFlashing_on();
	virtual void initFlashing_on();
	void testFlashingMinDuration_on_deferred();
	virtual void initFlashingMinDuration_on_deferred();
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		s.push_back(CUTE_SMEMFUN(DerivedTest, testConstuctor));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testOFF_flash));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOFFMinDuration_flash_deferred));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_off));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashingMinDuration_off_deferred));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_on));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashingMinDuration_on_deferred));

		return s;
	}
	//==============================
	// Types
	//==============================
	using SUT = CR::CrossRoad;
	using IntervalDuration = Mock::MockTimer::IntervalDuration;
protected:
	virtual std::unique_ptr<SUT> createSUT() {
			return std::unique_ptr<SUT>(
					new SUT(a1, a2, a3, timer)
			);
		}
	SUT& getSUT(){
			if(!pSUT)
				pSUT = createSUT();
			return *pSUT;
		}

	// Member
	Mock::ResultManager rm;
	Mock::MockTrafficLight a1, a2, a3;
	Mock::MockTimer timer;
	std::unique_ptr<SUT> pSUT;
};
//=====================================
// start Tests
//=====================================
inline
void CrossRoadStartTest::testConstuctor(){
	rm.beginInit();
	initConstructor();
	rm.endInit();

	rm.beginTest();
	getSUT();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initConstructor(){
	a1.off(); a2.off(); a3.off();
}
//--------------------------------
inline
void CrossRoadStartTest::testOFF_flash(){
	rm.beginInit();
	initOFF_flash();
	rm.endInit();

	auto &sut = getSUT();
	rm.beginTest();
	sut.flash();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initOFF_flash(){
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();

}
//--------------------------------
inline
void CrossRoadStartTest::testFlashing_off(){
	rm.beginInit();
	initFlashing_off();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing

	rm.beginTest();
	sut.off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initFlashing_off(){
	a1.off(); a2.off(); a3.off();
	timer.setIntervalDuration(IntervalDuration(SUT::OffMinDuration));
	timer.startTimer();

}
//--------------------------------
inline
void CrossRoadStartTest::testFlashingMinDuration_off_deferred(){
	rm.beginInit();
	initFlashingMinDuration_off_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration

	rm.beginTest();
	sut.off(); // deferred
	timer.tick(); // Flashing->off->OffMinDuration
	rm.endTest();

//	ASSERT_EQUAL(timer.getIntervalDuration().count(), SUT::OffMinDuration);
	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initFlashingMinDuration_off_deferred(){
	timer.stopTimer();
	a1.off(); a2.off(); a3.off();
	timer.setIntervalDuration(IntervalDuration(SUT::OffMinDuration));
	timer.startTimer();
}
//--------------------------------
inline
void CrossRoadStartTest::testOFFMinDuration_flash_deferred(){
	rm.beginInit();
	initOFFMinDuration_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.off();		// OffMinDuration

	sut.flash();	// -> deferred

	rm.beginTest();
	timer.tick();	// Off->flash->FlashingMinDuration
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initOFFMinDuration_flash_deferred(){
	timer.stopTimer();
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();
}
//--------------------------------
void CrossRoadStartTest::testFlashing_on(){
	rm.beginInit();
	initFlashing_on();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();
	timer.tick(); // Flashing

	rm.beginTest();
	sut.on();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initFlashing_on(){
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorFlashing));
	timer.startTimer();
}
//--------------------------------
inline
void CrossRoadStartTest::testFlashingMinDuration_on_deferred(){
	rm.beginInit();
	initFlashingMinDuration_on_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration

	rm.beginTest();
	sut.on(); // deferred
	timer.tick(); // Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadStartTest::initFlashingMinDuration_on_deferred(){
	timer.stopTimer();
		a1.switchOver(); a2.switchOver(); // Yellow
		timer.setIntervalDuration(IntervalDuration(SUT::MinorFlashing));
		timer.startTimer();
}

#endif /* INCLUDE_CROSSROADSTARTTEST_HPP_ */
