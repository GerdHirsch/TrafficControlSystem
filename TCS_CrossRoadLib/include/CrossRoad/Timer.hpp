/*
 * Timer.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_CROSSROAD_TIMER_HPP_
#define INCLUDE_CROSSROAD_TIMER_HPP_

namespace CrossRoad{
class CrossRoad;

class Timer{
public:
	virtual void add(CrossRoad& crossRoad) = 0;
	virtual void setCallBack(void (CrossRoad::*)() ) = 0;
	virtual void setIntervalDuration(std::chrono::milliseconds nextInterval) = 0;
	virtual void stopTimer() = 0;
	virtual void startTimer() = 0;
};

}



#endif /* INCLUDE_CROSSROAD_TIMER_HPP_ */
