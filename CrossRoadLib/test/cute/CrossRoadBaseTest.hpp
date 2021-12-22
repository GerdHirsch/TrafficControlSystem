/*
 * CrossRoadTest.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_CROSSROADBASETEST_HPP_
#define INCLUDE_CROSSROADBASETEST_HPP_

#include "CrossRoad/CrossRoad.hpp"
#include "CrossRoad/Mocks/DurationStreamOperator.hpp"
#include "CrossRoad/Mocks/EnumStreamOperator.hpp"
#include "CrossRoad/Mocks/MockTimer.hpp"
#include "CrossRoad/Mocks/MockTrafficLight.hpp"
#include <cute/cute.h>
#include <memory>


namespace CR = CrossRoadLib;

class CrossRoadBaseTest {
public:
  using this_type = CrossRoadBaseTest;
  CrossRoadBaseTest()
      : rm(), a1("a1", rm), a2("a2", rm), a3("a3", rm), timer(rm) {}

  //	void testOperation_defect();
  //	virtual void initOperation_defect();
public:
  //==============================
  // Types
  //==============================
  using SUT = CR::CrossRoad;
  using IntervalDuration = Mock::MockTimer::IntervalDuration;

protected:
  virtual std::unique_ptr<SUT> createSUT() {
    return std::unique_ptr<SUT>(new SUT(a1, a2, a3, timer));
  }
  SUT &getSUT() {
    if (!pSUT)
      pSUT = createSUT();
    return *pSUT;
  }

  // Member
  Mock::ResultManager rm;
  Mock::MockTrafficLight a1, a2, a3;
  Mock::MockTimer timer;
  std::unique_ptr<SUT> pSUT;
};

#endif /* INCLUDE_CROSSROADBASETEST_HPP_ */
