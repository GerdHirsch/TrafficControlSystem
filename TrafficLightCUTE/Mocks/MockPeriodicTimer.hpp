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

#include <string>

namespace SPT = SimplePeriodicTimer;

template<class Receiver>
class MockPeriodicTimer : public SPT::PeriodicTimer<Receiver>{
public:
	using this_type = MockPeriodicTimer<Receiver>;
	using base_type = SPT::PeriodicTimer<Receiver>;

	using MemberFunction = typename base_type::MemberFunction;
	using IntervalDuration = unsigned long long;
	//==========================
	// Timer Interface
	//==========================
	virtual void addReceiver(Receiver& receiver){
		this->receiver = &receiver;
	};
	bool hasReceiver() const { return receiver != nullptr; }
	virtual void removeReceiver(Receiver&  receiver){
		if(this->receiver == &receiver){
			this->receiver = nullptr;
		}
	};
	virtual void setCallback(this_type::MemberFunction function){
		this->function = function;
	};
	bool hasCallback() const { return function != nullptr; }

	virtual void setIntervalDuration(unsigned long long intervalDuration){
		resultManager->addString("setI:");
		resultManager->addString(std::to_string(intervalDuration));
		resultManager->addString(("|"));
		this->intervalDuration = intervalDuration;
	};

	//==========================
	// Test Interface
	//==========================
	MockPeriodicTimer(Mock::ResultManager& resultManager) : resultManager(&resultManager)
	{}
	void tick(){
		if(receiver && function){
			(receiver->*function)();
		}
	}
private:
	Mock::ResultManager *resultManager;
	IntervalDuration intervalDuration;
	Receiver* receiver=nullptr;
	MemberFunction function=nullptr;

};



#endif /* MOCKS_MOCKPERIODICTIMER_HPP_ */
