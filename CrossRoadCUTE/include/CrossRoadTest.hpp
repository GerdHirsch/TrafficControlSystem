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

#include <CrossRoad/CrossRoad.hpp>

#include "cute.h"

namespace CR = CrossRoadLib;

class CrossRoadTest{
public:
	using this_type = CrossRoadTest;
	CrossRoadTest()
	:
		resultManager(),
		timer(resultManager),
		a1(resultManager), a2(resultManager), a3(resultManager)
	{}
	// Tests
	void ConstuctorTest();

	// Types
	using SUT = CR::CrossRoad;
	SUT createSUT(){
		return CR::CrossRoad(a1, a2, a3, timer);
	}
	// Member
	Mock::ResultManager resultManager;
	Mock::MockTimer timer;
	Mock::MockTrafficLight a1, a2, a3;
public:
	template<class DerivedTest = this_type>
	static cute::suite make_suite(){
		cute::suite s { };
		s.push_back(CUTE_SMEMFUN(DerivedTest, ConstuctorTest));

		return s;
	}
};
inline
void CrossRoadTest::ConstuctorTest(){
	ASSERTM("Todo implement Test", false);
}




#endif /* INCLUDE_CROSSROADTEST_HPP_ */
