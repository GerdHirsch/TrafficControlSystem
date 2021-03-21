/*
 * PeriodicTimerMock.hpp
 *
 *  Created on: 21.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKPERIODICTIMER_HPP_
#define MOCKS_MOCKPERIODICTIMER_HPP_

#include <PeriodicTimer/PeriodicTimer.hpp>
#include <Mock/ResultManager.hpp>


namespace SPT = SimplePeriodicTimer;

template<class Receiver>
class MockPeriodicTimer : public SPT::PeriodicTimer<Receiver>{
public:
	using this_type = MockPeriodicTimer<Receiver>;
	using base_type = SPT::PeriodicTimer<Receiver>;

	using MemberFunction = typename base_type::MemberFunction;
	using IntervalDuration = unsigned long long;
	// Timer Interface
	virtual void addReceiver(Receiver&)=0;
	virtual void removeReceiver(Receiver&)=0;
	virtual void setCallback(this_type::MemberFunction function)=0;
	virtual void setIntervalDuration(unsigned long long intervalDuration)=0;

// Test Interface
	void tick(){
		(receiver->*function)();
	}
private:
	IntervalDuration intervalDuration;
	Receiver* receiver=nullptr;
	MemberFunction function=nullptr;
	Mock::ResultManager *resultManager;

};



#endif /* MOCKS_MOCKPERIODICTIMER_HPP_ */
