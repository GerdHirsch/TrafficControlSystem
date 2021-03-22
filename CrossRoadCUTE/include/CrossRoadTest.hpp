/*
 * CrossRoadTest.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_CROSSROADTEST_HPP_
#define INCLUDE_CROSSROADTEST_HPP_

#include "../Mocks/MockTrafficLight.hpp"
#include "../Mocks/MockTimer.hpp"

#include <CrossRoad/CrossRoad.hpp>

#include "cute.h"

#include <memory>

namespace CR = CrossRoadLib;

class CrossRoadTest{
public:
	using this_type = CrossRoadTest;
	CrossRoadTest()
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
	void testOFFMinDuration_flash();
	virtual void initOFFMinDuration_flash();

	void testFlashing_flash(); // ignore event
//
//	void testFlashing_off();
//	virtual void initFlashing_off();
//	void testFlashingMinDuration_off_deferred();
//	virtual void initFlashingMinDuration_off_deferred();
//
//	void testFlashing_on();
//	virtual void initFlashing_on();
//	void testFlashingMinDuration_on_deferred();
//	virtual void initFlashingMinDuration_on_deferred();
//
//	void testMajorDrive_flash();
//	virtual void initMajorDrive_flash();
//
//	// deferred from all states but MajorDrive
//	void testOperation_flash_deferred();
//	virtual void initOperation_flash_deferred();
//
//	// tests priority: regulateTraffic=0, flash=1
//	void testOperation_regulateTrafficAndflash_deferred();
//	virtual void initOperation_regulateTrafficAndflash_deferred();
//
//	void testOperation_regulateTraffic();
//	virtual void initOperation_regulateTraffic();
//
//	// deferred from 3 States: MinorYellow, MajorRedYellow, MajorMinDuration
//	void testMajorMinDuration_regulateTraffic_deferred();
//	virtual void initMajorMinDuration_regulateTraffic_deferred();
//
//	void testOperation_defect();
//	virtual void initOperation_defect();


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

public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		s.push_back(CUTE_SMEMFUN(DerivedTest, testConstuctor));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOFF_flash));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOFFMinDuration_flash));

		return s;
	}
};
//===========================================
inline
void CrossRoadTest::testConstuctor(){
	rm.beginInit();
	initConstructor();
	rm.endInit();

	rm.beginTest();
	getSUT();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initConstructor(){
	a1.off(); a2.off(); a3.off();
}
//--------------------------------
inline
void CrossRoadTest::testOFF_flash(){
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
void CrossRoadTest::initOFF_flash(){
	a1.flash(); a2.flash(); a3.flash();

}
//--------------------------------
inline
void CrossRoadTest::testOFFMinDuration_flash(){
	rm.beginInit();
	initOFFMinDuration_flash();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration
	timer.tick();
	sut.off(); // OffMinDuration

	rm.beginTest();
	sut.flash(); // deferred
	timer.tick(); // Off->flash->FlashingMinDuration
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initOFFMinDuration_flash(){
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();

}




#endif /* INCLUDE_CROSSROADTEST_HPP_ */
