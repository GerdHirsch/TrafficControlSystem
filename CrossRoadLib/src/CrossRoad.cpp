
#include <CrossRoad/CrossRoad.hpp>

#include <string>
#include <iostream>
#include <chrono>

using namespace std;
namespace CrossRoadLib {
//==========================================
// public Interface
//==========================================
// Ctor/Dtor
CrossRoad::CrossRoad(
		TrafficLight& a1,
		TrafficLight& a2,
		TrafficLight& a3,
		Timer& timer)
//		SPT::PeriodicTimer<CrossRoad>& timer)
:
	currentState(States::Off)
	, a1(&a1), a2(&a2), a3(&a3)
	, timer(&timer)
	, regulateTrafficDeferred(false), flashDeferred(false)
{
	entryOff();
	this->timer->add(*this);
	this->timer->setCallback(&CrossRoad::trigger);

	//	static bool registerCallback = true;
//	if(registerCallback){
//		registerCallback = false;
//		this->timer->setCallback(&CrossRoad::trigger);
//	}
}
//==========================================
void CrossRoad::flash()
{
	using namespace std;

	Guard guard = tryLock();

	if(currentState == States::MajorDrive || currentState == States::Off)
	{
		a1->flash();
		a2->flash();
		a3->flash();

		this->setState(States::Flashing);
		flashDeferred = false;
	}
	else if(currentState != States::Flashing )
	{
		std::cout << "CrossRoad::flash() deferred state: " << stateToString() << std::endl;
		flashDeferred = true;
	}
	else
	{
		std::cout << "CrossRoad.flash() in state " << stateToString() << " ignore" << std::endl;
	}
}
//------------------------------------------
void CrossRoad::on(){
	Guard guard = tryLock();

	if(currentState == States::Flashing){
		a1->switchOver();
		a2->switchOver();
		setState(States::MinorFlashing);
		wait(Times::MinorFlashing);
		timer->startTimer();
//		timer->addReceiver(*this);
	}
	// else ignore event on()
}
//------------------------------------------
void CrossRoad::regulateTraffic(){
	Guard guard = tryLock();

	if(currentState == States::MajorDrive){
		a1->switchOver();
		a2->switchOver();
		regulateTrafficDeferred = false;
		setState(States::MajorYellow);
		wait(Times::MajorYellow);
		timer->startTimer();
//		timer->addReceiver(*this);
	}else if(currentState != States::Off
			&& currentState != States::Flashing){
		regulateTrafficDeferred = true;
		std::cout << "CrossRoad::regulateTraffic() deferred state: " << stateToString() << std::endl;

	}
	// else ignore event regulateTraffic
}
//------------------------------------------
void CrossRoad::off(){
	Guard guard = tryLock();

	if(currentState == States::Flashing){
		setState(States::Off);
		a1->off();
		a2->off();
		a3->off();
	}
	// else ignore event off
}
//------------------------------------------
void CrossRoad::defect(){
	Guard guard = tryLock();

	if(currentState == States::Flashing){
		setState(States::Defect);
		a1->off();
		a2->off();
		a3->off();
		cout << "CrossRoad::defect removeReceiver(*this)" << endl;
		timer->stopTimer();
//		timer->removeReceiver(*this);
	// all other states
	}else if(currentState != States::Off
			&& currentState != States::Defect){
		setState(States::Defect);
		a1->flash();
		a2->flash();
		a3->flash();
		wait(Times::FlashingMinDuration);
		timer->startTimer();
//		timer->addReceiver(*this);
	}
	//else ignore
}
//==========================================
//Internal Operations
//==========================================
// Timer loop trigger
void CrossRoad::trigger(){
	Guard guard = tryLock();

	switch(currentState){
	case States::MinorFlashing:
		setState(States::MinorYellow);
		entryMinorYellow();
		wait(Times::MinorYellow);
		break;
	case States::MinorYellow:
		setState(States::MajorRedYellow);
		entryMajorRedYellow();
		wait(Times::MajorRedYellow);
		break;
	case States::MajorRedYellow:
		setState(States::MajorMinDuration);
		entryMajorMinDuration();
		wait(Times::MajorMinDuration);
		break;
	case States::MajorMinDuration:
		setState(States::MajorDrive);
		entryMajorDrive();
		cout << "CrossRoad::trigger MajorMinDuration removeReceiver(*this)" << endl;
		timer->stopTimer();
//		timer->removeReceiver(*this);

		//handle deferred events
		if(flashDeferred){ // Priority = 1
			guard.unlock();
			flash();
		}
		else if(regulateTrafficDeferred){ // Priority = 0
			guard.unlock();
			regulateTraffic();
		}
		break;
	case States::MajorYellow:
		setState(States::MinorRedYellow);
		entryMinorRedYellow();
		wait(Times::MinorRedYellow);
		break;
	case States::MinorRedYellow:
		setState(States::MinorDrive);
		entryMinorDrive();
		wait(Times::MinorDrive);
		break;
	case States::MinorDrive:
		setState(States::MinorYellow);
		entryMinorYellow();
		wait(Times::MinorYellow);
		break;

	case States::FlashingMinDuration:
	case States::Off:
	default:
		cout << "CrossRoad::trigger default removeReceiver(*this)" << endl;
		timer->stopTimer();
//		timer->removeReceiver(*this);
		break;
	}

}
//==========================================
void CrossRoad::setState(States state){
	currentState = state;
}
//------------------------------------------
void CrossRoad::wait(unsigned long long msDuration){
	timer->setIntervalDuration(IntervalDuration(msDuration));
//	timer->setIntervalDuration(msDuration);
}
//------------------------------------------
CrossRoad::Guard CrossRoad::tryLock(){
	static constexpr IntervalDuration tryLockDuration{10};
	Guard guard(myMutex, std::defer_lock);
	while(!guard.try_lock_for(tryLockDuration))
		;
	return guard;
}
//================================================
// entry behaviors
void CrossRoad::entryOff(){
	a1->off();
	a2->off();
	a3->off();
}
void CrossRoad::entryFlashing(){
	a1->flash();
	a2->flash();
	a3->flash();
}
void CrossRoad::entryMinorFlashing(){
	a1->switchOver(); // Yellow
	a2->switchOver();
}
void CrossRoad::entryMinorYellow(){
	a1->switchOver(); // Red
	a2->switchOver();
	a3->switchOver(); // Yellow
}
void CrossRoad::entryMajorRedYellow(){
	a1->switchOver(); // RedYellow
	a2->switchOver();
	a3->switchOver(); // Red
}
void CrossRoad::entryMajorMinDuration(){
	a1->switchOver(); // Green
	a2->switchOver();
}
void CrossRoad::entryMajorDrive(){
	// do nothing?
}
void CrossRoad::entryMajorYellow(){
	a1->switchOver(); // Yellow
	a2->switchOver();
}
void CrossRoad::entryMinorRedYellow(){
	a1->switchOver(); // Red
	a2->switchOver();
	a3->switchOver(); // RedYellow
}
void CrossRoad::entryMinorDrive(){
	a3->switchOver(); // Green
}
//------------------------------------------
std::string CrossRoad::stateToString()const{
	switch(currentState){
	case States::Off:
		return "Off";
	case States::Flashing:
		return "Flashing";
	case States::MinorFlashing:
		return "MinorFlashing";
	case States::MinorYellow:
		return "MinorYellow";
	case States::MajorRedYellow:
		return "MajorRedYellow";
	case States::MajorDrive:
		return "MajorDrive";
	case States::MajorMinDuration:
		return "MajorMinDuration";
	case States::MajorYellow:
		return "MajorYellow";
	case States::MinorRedYellow:
		return "MinorRedYellow";
	case States::MinorDrive:
		return "MinorDrive";
	default:
		return "no State ??";
	}
}

} // namespace CrossRoadLib
