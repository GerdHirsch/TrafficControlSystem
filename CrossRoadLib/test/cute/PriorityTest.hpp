/*
 * PriorityRegulateTrafficFlashOffTest.hpp
 *
 *  Created on: 27.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_PRIORITYTEST_HPP_
#define INCLUDE_PRIORITYTEST_HPP_

#include "RegulateTrafficDeferredTest.hpp"

class PriorityTest : public RegulateTrafficDeferredTest{
	using this_type = PriorityTest;

	// =======================================================
	// tests priority: regulateTraffic=0, off=1, flash=2
	// =======================================================
//	void testOperation_flashAndoff_deferred();
	void testOperation_regulateTrafficAndflash_deferred();

	void testOperation_flash_off_And_regulateTraffic_deferred();
	virtual void initOperation_flash_off_And_regulateTraffic_deferred();

	void testOperation_off_And_regulateTraffic_deferred();
	void testOperation_flash_After_off_And_regulateTraffic_deferred();
	void initOperation_flash_After_off_And_regulateTraffic_deferred();

	void testOperation_regulateTraffic_off_deferred_();
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };

		// regulateTraffic and flash deferred
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_regulateTrafficAndflash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flash_off_And_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_off_And_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flash_After_off_And_regulateTraffic_deferred));
//		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_flashAndoff_deferred));


		return s;
	}
};

//===========================================
//--------------------------------
// test priority regulateTraffic and flash deferred
//--------------------------------
void PriorityTest::testOperation_regulateTrafficAndflash_deferred(){

	rm.beginInit();
	initOperation_flash_deferred();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing
	timer.tick();	// MinorYellow

	sut.regulateTraffic();	// -> deferred prio=0

	timer.tick();	// MajorRedYellow

	sut.flash();	// -> deferred prio=2

	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
// test priority flash, off and regulateTraffic deferred
//--------------------------------
void PriorityTest::testOperation_flash_off_And_regulateTraffic_deferred(){
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
void PriorityTest::initOperation_flash_off_And_regulateTraffic_deferred(){
	initOperation_flash_deferred();
	initFlashingMinDuration_off_deferred();
}
//--------------------------------
void PriorityTest::testOperation_off_And_regulateTraffic_deferred(){
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
void PriorityTest::testOperation_flash_After_off_And_regulateTraffic_deferred(){
	rm.beginInit();
	initOperation_flash_After_off_And_regulateTraffic_deferred();
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
	timer.tick();	// MajorDrive -> FlashingMinDuration
	timer.tick();	// Flashing -> stop Timer
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
void PriorityTest::initOperation_flash_After_off_And_regulateTraffic_deferred(){
	initOperation_flash_deferred();
	initStopTimer();
}



#endif /* INCLUDE_PRIORITYTEST_HPP_ */
