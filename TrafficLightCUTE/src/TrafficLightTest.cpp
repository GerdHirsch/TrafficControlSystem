/*
 * AmpelTest.cpp
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#include "../include/TrafficLightTest.h"

void TrafficLightTest::testConstructor(){

	rm.beginInit();
	initConstructor();
	rm.endInit();


	rm.beginTest();
	createSUT();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
//	ASSERT_EQUAL(true, rm.success());
}
void TrafficLightTest::testFlashing_off(){
	auto sut = createSUT();

	rm.beginInit();
	initFlashing_off();
	rm.endInit();

	sut->flash();

	rm.beginTest();
	sut->off();
	rm.endTest();

	ASSERT_EQUAL(rm.getExpected(), rm.getResult());
}
