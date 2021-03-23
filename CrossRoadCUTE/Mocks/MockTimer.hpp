/*
 * MockTimer.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKTIMER_HPP_
#define MOCKS_MOCKTIMER_HPP_


#include <Mock/ResultManager.hpp>
#include <CrossRoad/Timer.hpp>
#include <CrossRoad/CrossRoad.hpp>

#include <string>


namespace Mock{

namespace CR = CrossRoadLib;


class MockTimer : public CR::Timer{
private:
	IntervalDuration intervalDuration;
	CR::CrossRoad* crossRoad=nullptr;
	CallbackType function=nullptr;
	ResultManager *resultManager;

public:

	MockTimer(ResultManager& resultManager)
	:
		intervalDuration(IntervalDuration(0))
		, resultManager(&resultManager)
	{}

	// Timer Interface
	virtual void add(CR::CrossRoad& crossRoad) override;
	virtual void setCallback(CallbackType callback) override;
	virtual void setIntervalDuration(IntervalDuration nextInterval) override;
	virtual void stopTimer() override;
	virtual void startTimer() override;

	// Test Interface
	void tick(){ (crossRoad->*function)(); }
	bool hasReceiver() const { return crossRoad != nullptr; }
	bool hasCallback() const { return function != nullptr; }

	IntervalDuration getIntervalDuration(){ return intervalDuration;}
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
	resultManager->addString("Interval:");
	resultManager->addString( std::to_string(nextInterval.count()) );
	resultManager->addString("|");

}
inline
void MockTimer::stopTimer(){
	resultManager->addString("stopTimer|");
}
inline
void MockTimer::startTimer(){
	resultManager->addString("startTimer|");

}

} // namespace Mock
#endif /* MOCKS_MOCKTIMER_HPP_ */
