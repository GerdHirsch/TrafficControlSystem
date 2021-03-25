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
#include "../Mocks/EnumStreamOperator.hpp"

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
	// =======================================================
	// test trigger
	// =======================================================
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
	// =======================================================
	// deferred flash from all Operation states but MajorDrive
	// =======================================================
	virtual void initOperation_flash_deferred();

	void testMinorYellow_flash_defered();
	void testMajorRedYellow_flash_defered();
	void testMajorMinDuration_flash_deferred();
	void testMajorYellow_flash_deferred();
	void testMinorRedYellow_flash_deferred();
	void testMinorDrive_flash_deferred();
	// =======================================================
	// deferred regultateTraffic from MinorYellow, MajorRedYellow, MajorMinDuration
	// =======================================================
	virtual void initOperation_regulateTraffic_deferred();

	void testMinorYellow_regulateTraffic_deferred();
	void testMajorRedYellow_regulateTraffic_deferred();
	void testMajorMinDuration_regulateTraffic_deferred();
	// =======================================================
	// tests priority: regulateTraffic=0, off=1, flash=2
	// =======================================================
//	void testOperation_flashAndoff_deferred();
	void testOperation_regulateTrafficAndflash_deferred();

	void testOperation_flash_off_And_regulateTraffic_deferred();
	virtual void initOperation_flash_off_And_regulateTraffic_deferred();

	void testOperation_off_And_regulateTraffic_deferred();
	void testOperation_flash_After_off_And_regulateTraffic_deferred();
	void testOperation_regulateTraffic_off_deferred_();

//	void testOperation_regulateTrafficAndoff_deferred();

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
		// flash deferred
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorYellow_flash_defered));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorRedYellow_flash_defered));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorMinDuration_flash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorYellow_flash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorRedYellow_flash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorDrive_flash_deferred));
		// regulateTraffic deferred
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorYellow_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorRedYellow_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorMinDuration_regulateTraffic_deferred));
		// regulateTraffic and flash deferred
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flash_off_And_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_off_And_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flash_After_off_And_regulateTraffic_deferred));
//		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flashAndoff_deferred));


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
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing

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
// trigger
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
//--------------------------------
// Operation flash deferred
//--------------------------------
inline
void CrossRoadTest::initOperation_flash_deferred(){
	timer.stopTimer();
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();
}
//--------------------------------
void CrossRoadTest::testMinorYellow_flash_defered(){
	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.flash();	// -> deferred

	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick(); // MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testMajorRedYellow_flash_defered(){
	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow

	sut.flash();	// -> deferred

	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick(); // MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------

void CrossRoadTest::testMajorMinDuration_flash_deferred(){
	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	sut.flash();	// -> deferred

	rm.beginTest();
	timer.tick();	// MajorDrive stopTimer
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testMajorYellow_flash_deferred(){
	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive
	sut.regulateTraffic();	// MajorYellow

	sut.flash();	// -> deferred

	timer.tick();	// MinorRedYellow
	timer.tick();	// MinorDrive
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testMinorRedYellow_flash_deferred(){
	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive
	sut.regulateTraffic();	// MajorYellow
	timer.tick();	// MinorRedYellow

	sut.flash();	// -> deferred

	timer.tick();	// MinorDrive
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MinorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testMinorDrive_flash_deferred(){
	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	sut.regulateTraffic();	// MajorDrive
	timer.tick();	// MajorYellow
	timer.tick();	// MinorRedYellow
	timer.tick();	// MinorDrive

	sut.flash();	// -> deferred

	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MinorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
// test priority regulateTraffic and flash deferred
//--------------------------------
void CrossRoadTest::testOperation_regulateTrafficAndflash_deferred(){

	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic();	// -> deferred prio=0
	sut.flash();	// -> deferred prio=2


	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
// test priority flash, off and regulateTraffic deferred
//--------------------------------
void CrossRoadTest::testOperation_flash_off_And_regulateTraffic_deferred(){
	rm.beginInit();
	initOperation_flash_off_And_regulateTraffic_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic(); // -> deferred prio=0
	sut.off();		// -> deferred prio=1
	sut.flash();	// -> deferred prio=2

	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
void CrossRoadTest::initOperation_flash_off_And_regulateTraffic_deferred(){
	initOperation_flash_deferred();
	initFlashingMinDuration_off_deferred();
}
//--------------------------------
void CrossRoadTest::testOperation_off_And_regulateTraffic_deferred(){
	rm.beginInit();
	initMajorMinDuration_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic(); // -> deferred prio=0
	sut.off();		// -> deferred prio=1

	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	timer.tick();	// MajorDrive process regulateTraffic, clear offDefered
	timer.tick();	// MinorRedYellow
	timer.tick();	// MinorDrive
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive stopTimer
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testOperation_flash_After_off_And_regulateTraffic_deferred(){
	rm.beginInit();
	initMajorMinDuration_trigger();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic(); // -> deferred prio=0
	sut.off();		// -> deferred prio=1

	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	timer.tick();	// MajorDrive process regulateTraffic, clear offDefered
	timer.tick();	// MinorRedYellow

	sut.flash();	// off must not be processed

	timer.tick();	// MinorDrive
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive stopTimer
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
// regulate Traffic deferred
//--------------------------------
inline
void CrossRoadTest::initOperation_regulateTraffic_deferred(){
	timer.stopTimer();
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MajorYellow));
	timer.startTimer();
}
//--------------------------------
void CrossRoadTest::testOperation_regulateTraffic_off_deferred_(){
	rm.beginInit();
	initOperation_regulateTraffic_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic(); // -> deferred prio=0
	sut.off();		// -> deferred prio=1

	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------

//--------------------------------
void CrossRoadTest::testMinorYellow_regulateTraffic_deferred(){
	rm.beginInit();
	initOperation_regulateTraffic_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic();	// ->deferred

	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testMajorRedYellow_regulateTraffic_deferred(){
	rm.beginInit();
	initOperation_regulateTraffic_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow

	sut.regulateTraffic();	// ->deferred

	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void CrossRoadTest::testMajorMinDuration_regulateTraffic_deferred(){
	rm.beginInit();
	initOperation_regulateTraffic_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	sut.regulateTraffic();	// ->deferred

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}

#endif /* INCLUDE_CROSSROADTEST_HPP_ */
