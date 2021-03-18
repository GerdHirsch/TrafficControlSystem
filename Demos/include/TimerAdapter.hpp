/*
 * TimerAdapter.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TIMERADAPTER_HPP_
#define INCLUDE_TIMERADAPTER_HPP_

#include <CrossRoad/Timer.hpp>
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include <chrono>

namespace Demo{

namespace CR = CrossRoadLib;
namespace SPR = SimplePeriodicTimer;

class TimerAdapter : public CR::Timer
{
public:
	using Duration = CR::Timer::IntervalDuration;
	using Function = CR::Timer::CallbackType;

	TimerAdapter(SPR::PeriodicTimer<CR::CrossRoad>& timer):timer(&timer)
	{ ; }
	// CrossRoadLib::Timer Interface
	virtual void add(CR::CrossRoad& crossRoad);
	virtual void setCallback(Function );
	virtual void setIntervalDuration(Duration nextInterval);
	virtual void startTimer();
	virtual void stopTimer();
private:
	SPR::PeriodicTimer<CR::CrossRoad> *timer = nullptr;
	CR::CrossRoad* crossRoad = nullptr;
	void (CR::CrossRoad::* function)() = nullptr;
};
inline
void TimerAdapter::add(CR::CrossRoad& crossRoad){
	this->crossRoad = &crossRoad;
	timer->addReceiver(crossRoad);
}
inline
void TimerAdapter::setCallback(Function function){
	this->function = function;
}
inline
void TimerAdapter::setIntervalDuration(Duration interval){
	timer->setIntervalDuration(interval.count());
}
inline
void TimerAdapter::startTimer(){
	timer->setCallback(function);
}
inline
void TimerAdapter::stopTimer(){
	timer->setCallback(nullptr);
}

} // namespace Demo





#endif /* INCLUDE_TIMERADAPTER_HPP_ */
