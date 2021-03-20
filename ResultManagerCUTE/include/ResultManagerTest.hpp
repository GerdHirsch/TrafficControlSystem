/*
 * ResultManagerTest.hpp
 *
 *  Created on: 19.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_RESULTMANAGERTEST_HPP_
#define INCLUDE_RESULTMANAGERTEST_HPP_

#include <Mock/ResultManager.hpp>
#include "cute.h"


class ResultManagerTest{
	using this_type = ResultManagerTest;
	// Tests
	void testTestSuccess();
	void testTestFailed();
	void testWrongExpected();

	// Types
	using SUT = Mock::ResultManager;
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		s.push_back(CUTE_SMEMFUN(DerivedTest, testTestSuccess));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testTestFailed));
		s.push_back(CUTE_SMEMFUN(DerivedTest, testWrongExpected));


		return s;
	}
};
inline
void ResultManagerTest::testTestSuccess(){
	SUT sut;
	sut.beginInit();
	sut.addString("expected");
	sut.endInit();
	sut.beginTest();
	sut.addString("expected");
	sut.endTest();

	ASSERTM("succeed", sut.succeed());
}
inline
void ResultManagerTest::testTestFailed(){
	SUT sut;
	sut.beginInit();
	sut.addString("expected");
	sut.endInit();
	sut.beginTest();
	sut.addString("result");
	sut.endTest();

	ASSERTM("succeed", !sut.succeed());
}
inline
void ResultManagerTest::testWrongExpected(){
	SUT sut;
	sut.beginInit();
	sut.addString(":expected");
	sut.endInit();
	sut.beginTest();
	sut.addString("expected");
	sut.endTest();

	ASSERTM("succeed", !sut.succeed());
}

#endif /* INCLUDE_RESULTMANAGERTEST_HPP_ */
