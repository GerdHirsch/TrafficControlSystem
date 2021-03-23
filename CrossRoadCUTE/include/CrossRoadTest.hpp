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
#include "../Mocks/DurationStreamOperator.hpp"

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

	void testMinorFlashing_trigger();
	virtual void initMinorFlashing_trigger();
	void testMinorYellow_trigger();
	virtual void initMinorYellow_trigger();
	void testMajorRedYellow_trigger();
	virtual void initMajorRedYellow_trigger();

	void testMajorMinDuration_trigger();
	virtual void initMajorMinDuration_trigger();

	void testMajorDrive_regulateTraffic();
	virtual void initMajorDrive_regulateTraffic();

	void testMajorYellow_trigger();
	virtual void initMajorYellow_trigger();
	void testMinorRedYellow_trigger();
	virtual void initMinorRedYellow_trigger();
	void testMinorDrive_trigger();
	virtual void initMinorDrive_trigger();

	void testMajorDrive_flash();
	virtual void initMajorDrive_flash();

//	// deferred from all states but MajorDrive
//	void testOperation_flash_deferred();
//	virtual void initOperation_flash_deferred();
//
//	// tests priority: regulateTraffic=0, flash=1
//	void testOperation_regulateTrafficAndflash_deferred();
//	virtual void initOperation_regulateTrafficAndflash_deferred();
//
//	// deferred from 3 States: MinorYellow, MajorRedYellow, MajorMinDuration
//	void testMajorMinDuration_regulateTraffic_deferred();
//	virtual void initMajorMinDuration_regulateTraffic_deferred();
//
//	void testOperation_defect();
//	virtual void initOperation_defect();
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

		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorFlashing_trigger));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorYellow_trigger));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorRedYellow_trigger));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorMinDuration_trigger));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorDrive_regulateTraffic));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorYellow_trigger));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorRedYellow_trigger));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorDrive_trigger));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorDrive_flash));

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
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();

}
//--------------------------------
inline
void CrossRoadTest::testFlashing_off(){
	rm.beginInit();
	initFlashing_off();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();
	timer.tick(); // Flashing

	rm.beginTest();
	sut.off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initFlashing_off(){
	a1.off(); a2.off(); a3.off();
	timer.setIntervalDuration(IntervalDuration(SUT::OffMinDuration));
	timer.startTimer();

}
//--------------------------------
inline
void CrossRoadTest::testFlashingMinDuration_off_deferred(){
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
void CrossRoadTest::initFlashingMinDuration_off_deferred(){
	timer.stopTimer();
	a1.off(); a2.off(); a3.off();
	timer.setIntervalDuration(IntervalDuration(SUT::OffMinDuration));
	timer.startTimer();
}
//--------------------------------
inline
void CrossRoadTest::testOFFMinDuration_flash_deferred(){
	rm.beginInit();
	initOFFMinDuration_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration
	timer.tick();
	sut.off(); // OffMinDuration

	rm.beginTest();
	sut.flash(); // deferred
	timer.tick(); // Off->flash->FlashingMinDuration
	rm.endTest();

//	ASSERT_EQUAL(timer.getIntervalDuration(), SUT::FlashingMinDuration);
	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initOFFMinDuration_flash_deferred(){
	timer.stopTimer();
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();
}
//--------------------------------
void CrossRoadTest::testFlashing_on(){
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
void CrossRoadTest::initFlashing_on(){
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorFlashing));
	timer.startTimer();
}
//--------------------------------
void CrossRoadTest::testFlashingMinDuration_on_deferred(){
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
void CrossRoadTest::initFlashingMinDuration_on_deferred(){
	timer.stopTimer();
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorFlashing));
	timer.startTimer();
}
//--------------------------------
void CrossRoadTest::testMinorFlashing_trigger(){
	rm.beginInit();
	initMinorFlashing_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration
	timer.tick(); // Flashing
	sut.on(); // MinorFlashing

	rm.beginTest();
	timer.tick(); // MinorYellow
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMinorFlashing_trigger(){
	a1.switchOver(); a2.switchOver(); // Red
	a3.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorYellow));
}
//--------------------------------
void CrossRoadTest::testMinorYellow_trigger(){
	rm.beginInit();
	initMinorYellow_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration
	timer.tick(); // Flashing
	sut.on(); // MinorFlashing
	timer.tick(); // MinorYellow

	rm.beginTest();
	timer.tick(); // MajorRedYellow
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMinorYellow_trigger(){
	a1.switchOver(); a2.switchOver(); // Yellow
	a3.switchOver(); // Red
	timer.setIntervalDuration(IntervalDuration(SUT::MajorRedYellow));
}
//--------------------------------
void CrossRoadTest::testMajorRedYellow_trigger(){
	rm.beginInit();
	initMajorRedYellow_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash(); // FlashingMinDuration
	timer.tick(); // Flashing
	sut.on(); // MinorFlashing
	timer.tick(); // MinorYellow
	timer.tick(); // MajorRedYellow

	rm.beginTest();
	timer.tick(); // MajorMinDuration
	timer.tick(); // MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMajorRedYellow_trigger(){
	a1.switchOver(); a2.switchOver(); // Green
	timer.setIntervalDuration(IntervalDuration(SUT::MajorMinDuration));
}
//--------------------------------
void CrossRoadTest::testMajorMinDuration_trigger(){
	rm.beginInit();
	initMajorMinDuration_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive stopTimer
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMajorMinDuration_trigger(){
	timer.stopTimer();
}
//--------------------------------
void CrossRoadTest::testMajorDrive_regulateTraffic(){
	rm.beginInit();
	initMajorDrive_regulateTraffic();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive stopTimer

	rm.beginTest();
	sut.regulateTraffic();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMajorDrive_regulateTraffic(){
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MajorYellow));
	timer.startTimer();
}
//--------------------------------
void CrossRoadTest::testMajorYellow_trigger(){
	rm.beginInit();
	initMajorYellow_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive stopTimer
	sut.regulateTraffic();

	rm.beginTest();
	timer.tick(); // MinorRedYellow
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMajorYellow_trigger(){
	a1.switchOver(); a2.switchOver(); // Red
	a3.switchOver(); // RedYellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorRedYellow));
}
//--------------------------------
void CrossRoadTest::testMinorRedYellow_trigger(){
	rm.beginInit();
	initMinorRedYellow_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive stopTimer
	sut.regulateTraffic();
	timer.tick();	// MinorRedYellow

	rm.beginTest();
	timer.tick();	// MinorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMinorRedYellow_trigger(){
	a3.switchOver(); // Green
	timer.setIntervalDuration(IntervalDuration(SUT::MinorDrive));
}
//--------------------------------
void CrossRoadTest::testMinorDrive_trigger(){
	rm.beginInit();
	initMinorDrive_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive stopTimer
	sut.regulateTraffic();
	timer.tick();	// MinorRedYellow
	timer.tick();	// MinorDrive

	rm.beginTest();
	timer.tick();	// MinorYellow
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMinorDrive_trigger(){
	a3.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorYellow));
}
//--------------------------------
inline
void CrossRoadTest::testMajorDrive_flash(){
	rm.beginInit();
	initMajorDrive_flash();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive stopTimer

	rm.beginTest();
	sut.flash();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
inline
void CrossRoadTest::initMajorDrive_flash(){
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();
}


#endif /* INCLUDE_CROSSROADTEST_HPP_ */
