/*
 * CrossRoadTimerAdapter.hpp
 *
 *  Created on: 05.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TCS_CROSSROADTIMERADAPTER_HPP_
#define INCLUDE_TCS_CROSSROADTIMERADAPTER_HPP_

#include <CrossRoad/Timer.hpp>
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include <chrono>

namespace TCS{

class CrossRoadTimerAdapter : public CrossRoadLib::Timer
{
public:
	using CrossRoad = CrossRoadLib::CrossRoad;
	using Duration = CrossRoadLib::Timer::IntervalDuration;
	using Function = CrossRoadLib::Timer::CallbackType;
	using Timer = SimplePeriodicTimer::PeriodicTimer<CrossRoad>;

	CrossRoadTimerAdapter(Timer& timer):timer(&timer)
	{ ; }
	// CrossRoadLib::Timer Interface
	virtual void add(CrossRoad& crossRoad);
	virtual void setCallback(Function );
	virtual void setIntervalDuration(Duration nextInterval);
	virtual void startTimer();
	virtual void stopTimer();
private:
	Timer *timer = nullptr;
	CrossRoad* crossRoad = nullptr;
	void (CrossRoad::* function)() = nullptr;
};
inline
void CrossRoadTimerAdapter::add(CrossRoad& crossRoad){
	this->crossRoad = &crossRoad;
	timer->addReceiver(crossRoad);
}
inline
void CrossRoadTimerAdapter::setCallback(Function function){
	this->function = function;
}
inline
void CrossRoadTimerAdapter::setIntervalDuration(Duration interval){
	timer->setIntervalDuration(interval.count());
}
inline
void CrossRoadTimerAdapter::startTimer(){
	timer->setCallback(function);
}
inline
void CrossRoadTimerAdapter::stopTimer(){
	timer->setCallback(nullptr);
}

} // namespace TCS

#endif /* INCLUDE_TCS_CROSSROADTIMERADAPTER_HPP_ */
