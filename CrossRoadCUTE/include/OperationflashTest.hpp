/*
 * FlashDeferedTest.hpp
 *
 *  Created on: 27.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_OPERATIONFLASHTEST_HPP_
#define INCLUDE_OPERATIONFLASHTEST_HPP_

#include "TriggerTest.hpp"

class Operation_flash_Test : public TriggerTest{
public:
	using this_type = Operation_flash_Test;

	// =======================================================
	// deferred flash from all Operation states but MajorDrive
	// =======================================================
	virtual void initOperation_flash_deferred();
	virtual void initMajorDrive_flash();

	void testMinorYellow_flash_defered();
	void testMajorRedYellow_flash_defered();
	void testMajorMinDuration_flash_deferred();
	void testMajorDrive_flash();
	void testMajorYellow_flash_deferred();
	void testMinorRedYellow_flash_deferred();
	void testMinorDrive_flash_deferred();
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		// flash deferred
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorYellow_flash_defered));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorRedYellow_flash_defered));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorMinDuration_flash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorDrive_flash));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorYellow_flash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorRedYellow_flash_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorDrive_flash_deferred));

		return s;
	}
};

//--------------------------------
// Operation flash deferred
//--------------------------------
inline
void Operation_flash_Test::initOperation_flash_deferred(){
	timer.stopTimer();
	initMajorDrive_flash();
}
//--------------------------------
inline
void Operation_flash_Test::initMajorDrive_flash(){
	a1.flash(); a2.flash(); a3.flash();
	timer.setIntervalDuration(IntervalDuration(SUT::FlashingMinDuration));
	timer.startTimer();
}
//--------------------------------
void Operation_flash_Test::testMinorYellow_flash_defered(){
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
void Operation_flash_Test::testMajorRedYellow_flash_defered(){
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
void Operation_flash_Test::testMajorMinDuration_flash_deferred(){
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
void Operation_flash_Test::testMajorDrive_flash(){
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
//--------------------------------
void Operation_flash_Test::testMajorYellow_flash_deferred(){
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
void Operation_flash_Test::testMinorRedYellow_flash_deferred(){
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
void Operation_flash_Test::testMinorDrive_flash_deferred(){
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


#endif /* INCLUDE_OPERATIONFLASHTEST_HPP_ */
