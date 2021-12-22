/*
 * DefectTest.hpp
 *
 *  Created on: 27.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_DEFECTTEST_HPP_
#define INCLUDE_DEFECTTEST_HPP_

#include "CrossRoadBaseTest.hpp"

class DefectTest : public CrossRoadBaseTest{
	using this_type = DefectTest;

	virtual void initDefect();

	void testOff_defect();
	void testFlashing_defect();
	// Operating
	void testMinorFlashing_defect();
//	void testMinorYellow_defect();
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };

		s.push_back(CUTE_SMEMFUN(DerivedTest, testOff_defect));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testFlashing_defect));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testMinorFlashing_defect));

		return s;
	}
};
//===========================
// defect tests
//===========================
void DefectTest::initDefect(){
	a1.flash(); a2.flash(); a3.flash();
	a1.off(); a2.off(); a3.off();
}
//---------------------------
void DefectTest::testOff_defect(){
	rm.beginInit();
	// no action
	rm.endInit();

	auto &sut = getSUT();

	rm.beginTest();
	sut.defect();		// Off
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
//---------------------------
void DefectTest::testFlashing_defect(){
	rm.beginInit();
	initDefect();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing

	rm.beginTest();
	sut.defect();		// Off
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());

}
//---------------------------
void DefectTest::testMinorFlashing_defect(){
	rm.beginInit();
	initDefect();
	rm.endInit();

	auto &sut = getSUT();
	sut.flash();	// FlashingMinDuration
	timer.tick();	// Flashing
	sut.on();		// MinorFlashing

	rm.beginTest();
	sut.defect();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());

}
//---------------------------

#endif /* INCLUDE_DEFECTTEST_HPP_ */
