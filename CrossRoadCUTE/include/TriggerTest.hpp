/*
 * CrossRoadTriggerTest.hpp
 *
 *  Created on: 26.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TRIGGERTEST_HPP_
#define INCLUDE_TRIGGERTEST_HPP_

#include "StartTest.hpp"

class TriggerTest : public StartTest{
public:
	using this_type = TriggerTest;

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
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };

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
};
//--------------------------------
// trigger
//--------------------------------
void TriggerTest::testMinorFlashing_trigger(){
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
void TriggerTest::initMinorFlashing_trigger(){
	a3.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorYellow));
}
//--------------------------------
void TriggerTest::testMinorYellow_trigger(){
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
void TriggerTest::initMinorYellow_trigger(){
	a1.switchOver(); a2.switchOver(); // Yellow
	a3.switchOver(); // Red
	timer.setIntervalDuration(IntervalDuration(SUT::MajorRedYellow));
}
//--------------------------------------
void TriggerTest::testMajorRedYellow_trigger(){
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
void TriggerTest::initMajorRedYellow_trigger(){
	a1.switchOver(); a2.switchOver(); // Green
	timer.setIntervalDuration(IntervalDuration(SUT::MajorMinDuration));
}
//--------------------------------
void TriggerTest::testMajorMinDuration_trigger(){
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
void TriggerTest::initMajorMinDuration_trigger(){
	timer.stopTimer();
}
//--------------------------------
void TriggerTest::testMajorDrive_regulateTraffic(){
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
void TriggerTest::initMajorDrive_regulateTraffic(){
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MajorYellow));
	timer.startTimer();
}
//--------------------------------
void TriggerTest::testMajorYellow_trigger(){
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
void TriggerTest::initMajorYellow_trigger(){
	a1.switchOver(); a2.switchOver(); // Red
	a3.switchOver(); // RedYellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorRedYellow));
}
//--------------------------------
void TriggerTest::testMinorRedYellow_trigger(){
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
void TriggerTest::initMinorRedYellow_trigger(){
	a3.switchOver(); // Green
	timer.setIntervalDuration(IntervalDuration(SUT::MinorDrive));
}
//--------------------------------
void TriggerTest::testMinorDrive_trigger(){
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
void TriggerTest::initMinorDrive_trigger(){
	a3.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MinorYellow));
}
inline
void TriggerTest::testMajorDrive_flash(){
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
void TriggerTest::initMajorDrive_flash(){
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();
}
#endif /* INCLUDE_TRIGGERTEST_HPP_ */
