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
	using this_type = CrossRoadTest;
	// Tests
	void ConstuctorTest();

	// Types
	using SUT = CR::CrossRoad;
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
