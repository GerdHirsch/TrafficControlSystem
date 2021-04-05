#ifndef INCLUDE_TCS_TRAFFICLIGHT_HPP_
#define INCLUDE_TCS_TRAFFICLIGHT_HPP_

#include <PeriodicTimer/PeriodicTimer.hpp>
#include <CrossRoad/TrafficLight.hpp>
#include <CrossRoad/ProtocolViolationException.hpp>

#include <string>
#include <iostream>
#include <mutex>
#include <chrono>
#include "Lamp.hpp"

namespace TCS{

class TrafficLight : public CrossRoadLib::TrafficLight{
public:
	using Mutex = std::timed_mutex;
	using Guard = std::unique_lock<Mutex>;
	using Timer = SimplePeriodicTimer::PeriodicTimer<TrafficLight>;

	TrafficLight(Lamp &red, Lamp &yellow, Lamp &green, Timer& timer, std::string name="tl")
	:
		currentState(Off)
		, red(&red), yellow(&yellow), green(&green)
		, timer(&timer)
		, name(std::move(name))
	{
		entryOff();
		this->timer->setCallback(&TrafficLight::doFlashing);
	}
	~TrafficLight(){
		timer->removeReceiver(*this);
	}
	enum States { Off, Flashing, Red, RedYellow, Yellow, Green};

	void switchOver(){
		Guard guard(myMutex);

		switch(currentState){
		case Flashing:
			currentState = Yellow;
			timer->removeReceiver(*this);
			entryYellow();
			break;
		case Yellow:
			currentState = Red;
			entryRed();
			break;
		case Red:
			currentState = RedYellow;
			entryRedYellow();
			break;
		case RedYellow:
			currentState = Green;
			entryGreen();
			break;
		case Green:
			currentState = Yellow;
			entryYellow();
			break;
		case Off:
		default:
			throw ProtocolViolationException("switchOver in State Off");
			break;
		}
	}
	void flash(){
		Guard guard(myMutex, std::defer_lock);
		std::chrono::milliseconds lockDuration(10);
		while(!guard.try_lock_for(lockDuration))
			;
		if(currentState != Flashing){
			currentState = Flashing;
			entryFlashing();
		}
	}
	void off(){
		Guard guard(myMutex);
		if(currentState != Flashing && currentState != Off){
			//std::cout << "off not in state Flashing" << std::endl;
			throw ProtocolViolationException("off in state Operation");
		}else if(currentState == Flashing){
			currentState = Off;
			entryOff();
		}
		// else if(currentState == Off) ignore event off()
	}
private:
	// callback for timer
	void doFlashing(){
		Guard guard (myMutex);

		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
		if(currentState != Flashing){
			//std::cout << name << " removeReceiver(*this)" << std::endl;
			timer->removeReceiver(*this);
		}
		if(yellow->isOn()) yellow->off();
		else yellow->on();
	}
	// state entry behaviors
	void entryRed(){
		red->on(); yellow->off(); green->off();
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
	}
	void entryRedYellow(){
		red->on(); yellow->on(); green->off();
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
	}
	void entryGreen(){
		red->off(); yellow->off(); green->on();
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
	}
	void entryYellow(){
		red->off(); yellow->on(); green->off();
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
	}
	void entryFlashing(){
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
		lampsOff();
		timer->addReceiver(*this);
	}
	void entryOff(){
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
		lampsOff();
	}
	void lampsOff(){
		red->off(); yellow->off(); green->off();
		//std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
	}
private:
	States currentState = Off;
	Lamp *red, *yellow, *green;
	Timer* timer;
	std::string name;
	Mutex myMutex;
};

} // namespace TCS


#endif /* INCLUDE_TCS_TRAFFICLIGHT_HPP_ */
