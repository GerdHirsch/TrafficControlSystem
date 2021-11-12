/*
 * RegulateTrafficDeferred.hpp
 *
 *  Created on: 27.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_REGULATETRAFFICDEFERREDTEST_HPP_
#define INCLUDE_REGULATETRAFFICDEFERREDTEST_HPP_

#include "OperationflashTest.hpp"

class RegulateTrafficDeferredTest : public Operation_flash_Test{
	using this_type = RegulateTrafficDeferredTest;

	//==============================
	// deferred regultateTraffic from MinorYellow, MajorRedYellow, MajorMinDuration
	// =======================================================
	virtual void initOperation_regulateTraffic_deferred();
	// regulteTraffic ignored
	void testOff_regulateTraffic_ignored();
	void testOff_regulateTraffic_notDeferred();
	void testFlashingMinDuration_regulateTraffic_ignored();
	void testFlashingMinDuration_regulateTraffic_notDeferred();
	void testFlashing_regulateTraffic_ignored();
	void testFlashing_regulateTraffic_notDeferred();
	void testMinorFlashing_regulateTraffic_ignored();
	void testMinorFlashing_regulateTraffic_notDeferred();
	void testMajorYellow_regulateTraffic_ignored();
	void testMajorYellow_regulateTraffic_notDeferred();

	// todo
	//	void testMinorRedYellow_regulateTraffic_ignored();
	//	void testMinorDrive_regulateTraffic_ignored();

	void testMinorYellow_regulateTraffic_deferred();
	void testMajorRedYellow_regulateTraffic_deferred();
	void testMajorMinDuration_regulateTraffic_deferred();

	// regulateTraffic prio=0, off prio=1
	// off will be discarded but regulateTraffic processed
	void testOperation_regulateTraffic_off_deferred();

public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		// regulateTraffic ignored
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_regulateTraffic_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_regulateTraffic_notDeferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashingMinDuration_regulateTraffic_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashingMinDuration_regulateTraffic_notDeferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_regulateTraffic_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_regulateTraffic_notDeferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorFlashing_regulateTraffic_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorFlashing_regulateTraffic_notDeferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorYellow_regulateTraffic_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorYellow_regulateTraffic_notDeferred));
		// regulateTraffic deferred
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorYellow_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorRedYellow_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorMinDuration_regulateTraffic_deferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOperation_regulateTraffic_off_deferred));

		return s;
	}
};
//--------------------------------
// regulate Traffic ignored
//--------------------------------
inline
void RegulateTrafficDeferredTest::testOff_regulateTraffic_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();	// Off

	rm.beginTest();
	sut.regulateTraffic();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testOff_regulateTraffic_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();	// Off
	sut.regulateTraffic();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testFlashingMinDuration_regulateTraffic_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();	// Off
	sut.flash();	// FlashingMinDuration

	rm.beginTest();
	sut.regulateTraffic();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testFlashingMinDuration_regulateTraffic_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();	// Off
	sut.flash();	// FlashingMinDuration
	sut.regulateTraffic();
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testFlashing_regulateTraffic_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();	// Off
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing

	rm.beginTest();
	sut.regulateTraffic();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testFlashing_regulateTraffic_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();	// Off
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.regulateTraffic();
	sut.on();		// MinorFlashing

	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testMinorFlashing_regulateTraffic_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	rm.beginTest();
	sut.regulateTraffic();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testMinorFlashing_regulateTraffic_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	sut.regulateTraffic();
	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration

	rm.beginTest();
	timer.tick();	// MajorDrive
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testMajorYellow_regulateTraffic_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive
	sut.regulateTraffic(); // MajorYellow

	rm.beginTest();
	sut.regulateTraffic();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void RegulateTrafficDeferredTest::testMajorYellow_regulateTraffic_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	timer.tick();	// MinorYellow
	timer.tick();	// MajorRedYellow
	timer.tick();	// MajorMinDuration
	timer.tick();	// MajorDrive
	sut.regulateTraffic(); // MajorYellow
	sut.regulateTraffic();
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
// regulate Traffic deferred
//--------------------------------
inline
void RegulateTrafficDeferredTest::initOperation_regulateTraffic_deferred(){
	timer.stopTimer();
	a1.switchOver(); a2.switchOver(); // Yellow
	timer.setIntervalDuration(IntervalDuration(SUT::MajorYellow));
	timer.startTimer();
}
//--------------------------------
void RegulateTrafficDeferredTest::testMinorYellow_regulateTraffic_deferred(){
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
void RegulateTrafficDeferredTest::testMajorRedYellow_regulateTraffic_deferred(){
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
void RegulateTrafficDeferredTest::testMajorMinDuration_regulateTraffic_deferred(){
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
//--------------------------------
void RegulateTrafficDeferredTest::testOperation_regulateTraffic_off_deferred(){
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


#endif /* INCLUDE_REGULATETRAFFICDEFERREDTEST_HPP_ */
