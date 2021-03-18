/*
 * MockTimer.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKTIMER_HPP_
#define MOCKS_MOCKTIMER_HPP_

#include <CrossRoad/Timer.hpp>
#include <CrossRoad/CrossRoad.hpp>
namespace CR = CrossRoadLib;



class MockTimer : public CR::Timer{
public:
	// Timer Interface
	virtual void add(CR::CrossRoad& crossRoad) override;
	virtual void setCallback(CallbackType callback) override;
	virtual void setIntervalDuration(IntervalDuration nextInterval) override;
	virtual void stopTimer() override;
	virtual void startTimer() override;
	// Test Interface
	void tick(){
		(crossRoad->*function)();
	}
//	bool addCalled(){
//		return crossRoad != nullptr;
//	}
//	bool setCallbackCalled(){
//		return function != nullptr;
//	}
//	bool stopTimerCalled(){
//		return false;
//	}
//	auto getIntervalDuration() -> decltype(intervalDuration.count())
//	{
//		return intervallDuration.count();
//	}
	IntervalDuration intervalDuration;
	CR::CrossRoad* crossRoad=nullptr;
	CallbackType function=nullptr;

};
inline
void MockTimer::add(CR::CrossRoad& crossroad){
	this->crossRoad = &crossroad;
}
inline
void MockTimer::setCallback(CallbackType callback){
	this->function = callback;
}
inline
void MockTimer::setIntervalDuration(IntervalDuration nextInterval){
	this->intervalDuration = nextInterval;
}
inline
void MockTimer::stopTimer(){

}
inline
void MockTimer::startTimer(){

}


#endif /* MOCKS_MOCKTIMER_HPP_ */
