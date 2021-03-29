#ifndef TRAFFICLIGHT_HPP_
#define TRAFFICLIGHT_HPP_

#include <CrossRoad/TrafficLight.hpp>

#include <PeriodicTimer/PeriodicTimer.hpp>

#include <string>
#include <iostream>
#include <mutex>
#include <chrono>
namespace Demo{

namespace SPT = SimplePeriodicTimer;
namespace CR = CrossRoadLib;

class TrafficLight : public CR::TrafficLight {
public:
	using Mutex = std::timed_mutex;
	using Guard = std::unique_lock<Mutex>;
	TrafficLight(std::string name, SPT::PeriodicTimer<TrafficLight>& timer)
	:
		currentState(Off)
		, name(std::move(name))
		, timer(&timer)
	{
		entryOff();
		static bool registerCallback = true;
		if(registerCallback){
			this->timer->setCallback(&TrafficLight::doFlashing);
			registerCallback = false;
		}

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
//			throw Exception;
			break;
		}
	}
	void flash(){
		Guard guard(myMutex, std::defer_lock);
		std::chrono::milliseconds lockDuration(10);
		while(!guard.try_lock_for(lockDuration))
			;
		currentState = Flashing;
		entryFlashing();
		timer->addReceiver(*this);
	}
	void off(){
		Guard guard(myMutex);
		if(currentState != Flashing && currentState != Off){
			std::cout << "off not in state Flashing" << std::endl;
			return; // throw Exception
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

		if(currentState != Flashing){
//			std::cout << name << " removeReceiver(*this)" << std::endl;
			timer->removeReceiver(*this);
		}else{
			std::cout << name << ".doFlashing()" << std::endl;
		}
	}
	// state entry behaviors
	void entryRed(){
		std::cout << name << ".entryRed()" << std::endl;
	}
	void entryRedYellow(){
		std::cout << name << ".entryRedYellow()" << std::endl;
	}
	void entryGreen(){
		std::cout << name << ".entryGreen()" << std::endl;
	}
	void entryYellow(){
		std::cout << name << ".entryYellow()" << std::endl;
	}
	void entryFlashing(){
		std::cout << name << ".entryFlashing()" << std::endl;
		lampsOff();
	}
	void entryOff(){
		std::cout << name << ".entryOff()" << std::endl;
		lampsOff();
	}
	void lampsOff(){
//		std::cout << name << ": " << __PRETTY_FUNCTION__ << std::endl;
	}
private:
	States currentState = Off;
	std::string name;
	SPT::PeriodicTimer<TrafficLight>* timer;
	Mutex myMutex;
};

} // namespace Demo


#endif /* TRAFFICLIGHT_HPP_ */
