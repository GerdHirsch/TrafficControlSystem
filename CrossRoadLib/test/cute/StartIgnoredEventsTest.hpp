/*
 * StartIgnoredEvents.hpp
 *
 *  Created on: 29.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_STARTIGNOREDEVENTSTEST_HPP_
#define INCLUDE_STARTIGNOREDEVENTSTEST_HPP_

#include "StartTest.hpp"

class StartIgnoredEventsTest : public StartTest{
public:
	using this_type = StartIgnoredEventsTest;

	// ignored events
	void testOff_off_ignored_AfterCtor(); // ignore event
	void testOff_off_notDeferred_AfterCtor(); // ignore event

	void testOff_off_ignored_AfterFlashing(); // ignore event
	void testOff_off_notDeferred_AfterFlashing(); // ignore event
	void testOffMinDuration_off_ignored(); // ignore event
	void testOffMinDuration_off_notDeferred(); // ignore event

	void testOffMinDuration_on_ignored();
	void testOffMinDuration_on_notDeferred();
//	void testOff_on_ignored();
//	void testOff_on_notDeferred();

	void testFlashing_flash_ignored(); // ignore event
	void testFlashing_flash_notDeferred(); // ignore event
	void testFlashingMinDuration_flash_ignored(); // ignore event
	void testFlashingMinDuration_flash_notDererred(); // ignore event

	void testMajorDrive_off_ignored(); // ignore event

	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		//ignored Events
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_off_ignored_AfterCtor));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_off_notDeferred_AfterCtor));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_off_ignored_AfterFlashing));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_off_notDeferred_AfterFlashing));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testOffMinDuration_off_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOffMinDuration_off_notDeferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOffMinDuration_on_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testOffMinDuration_on_notDeferred));

		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_flash_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_flash_notDeferred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashingMinDuration_flash_ignored));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashingMinDuration_flash_notDererred));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMajorDrive_off_ignored));


		return s;
	}
};

//--------------------------------
// ignore events
//--------------------------------
inline
void StartIgnoredEventsTest::testOff_off_ignored_AfterCtor(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();

	rm.beginTest();
	sut.off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOff_off_notDeferred_AfterCtor(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.off();
	sut.flash();

	rm.beginTest();
	timer.tick();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOff_off_ignored_AfterFlashing(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	sut.off();		// off -> deferred
	timer.tick();	// Flashing -> OffMinDuration
	timer.tick();	// OffMinDuration
	timer.tick();	// Off

	rm.beginTest();
	sut.off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOff_off_notDeferred_AfterFlashing(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	sut.off();		// off -> deferred
	timer.tick();	// Flashing -> OffMinDuration
	timer.tick();	// OffMinDuration
	sut.off();
	timer.tick();	// Off
	sut.flash();	// FlashingMinDuration

	rm.beginTest();
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOffMinDuration_off_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.off();		// OffMinDuration

	rm.beginTest();
	sut.off();		// ignore event
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOffMinDuration_off_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.off();		// OffMinDuration
	sut.off();		// ignore event
	timer.tick();	// Off
	sut.flash();	// FlashingMinDuration

	rm.beginTest();
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOffMinDuration_on_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.off();		// OffMinDuration

	rm.beginTest();
	sut.on();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testOffMinDuration_on_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.off();		// OffMinDuration
	sut.on();		// ignored
	timer.tick();	// Off
	sut.flash();	// FlashingMinDuration

	rm.beginTest();
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testFlashing_flash_ignored(){
	rm.beginInit();
	initIgnoreEvent();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing

	rm.beginTest();
	sut.flash();	// ignore event
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testFlashing_flash_notDeferred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.flash();	// ignore event
	sut.off();		// OffMinDuration

	rm.beginTest();
	timer.tick();	// Off
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testFlashingMinDuration_flash_ignored(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	sut.flash();	// ignore event

	rm.beginTest();
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
inline
void StartIgnoredEventsTest::testFlashingMinDuration_flash_notDererred(){
	rm.beginInit();
	initStopTimer();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	sut.flash();	// ignore event
	timer.tick();	// Flashing
	sut.off();		// OffMinDuration

	rm.beginTest();
	timer.tick();	// Off
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//--------------------------------
void StartIgnoredEventsTest::testMajorDrive_off_ignored(){
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
	sut.off();		// ignored
	sut.flash();	// FlashingMinDuration

	rm.beginTest();
	timer.tick();	// Flashing
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}


#endif /* INCLUDE_STARTIGNOREDEVENTSTEST_HPP_ */
