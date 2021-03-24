
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
	currentState(States::Off) // initialState
	, a1(&a1), a2(&a2), a3(&a3)
	, timer(&timer)
	, regulateTrafficDeferred(false), flashDeferred(false), offDeferred(false), onDeferred(false)
{
	entryOffMinDuration(); // ax.off() all trafficLights
	// configure Timer
	this->timer->add(*this);
	this->timer->setCallback(&CrossRoad::trigger);
}
//CrossRoad::CrossRoad(CrossRoad&& rhs)
//	:
//		currentState(rhs.currentState),
//		a1(rhs.a1), a2(rhs.a2), a3(rhs.a3),
//		timer(rhs.timer),
//		myMutex(),
//		regulateTrafficDeferred(rhs.regulateTrafficDeferred),
//		flashDeferred(rhs.flashDeferred)
//{
//
//}
//CrossRoad& CrossRoad::operator=(CrossRoad&& rhs){
//	currentState = rhs.currentState;
//	a1 = rhs.a1;
//	a2 = rhs.a2;
//	a3 = rhs.a3;
////	myMutex = std::move(rhs.myMutex); not moveable
//	regulateTrafficDeferred = rhs.regulateTrafficDeferred;
//	flashDeferred = rhs.flashDeferred;
//
//	return *this;
//}
//==========================================

void CrossRoad::flash()
{
	Guard guard = tryLock();

	if(currentState == States::MajorDrive || currentState == States::Off)
	{
		this->setState(States::FlashingMinDuration);
		entryFlashingMinDuration();
		flashDeferred = false;
		wait(Times::FlashingMinDuration);
		timer->startTimer();
	}
	else if(currentState != States::Flashing && currentState != States::FlashingMinDuration )
	{
		//std::cout << "CrossRoad::flash() deferred state: " << stateToString() << std::endl;
		flashDeferred = true;
	}
	else
	{
		//std::cout << "CrossRoad.flash() in state " << stateToString() << " ignore" << std::endl;
	}
}
//------------------------------------------
void CrossRoad::on(){
	Guard guard = tryLock();

	if(currentState == States::Flashing){
		setState(States::MinorFlashing);
		entryMinorFlashing();
		onDeferred = false;
		wait(Times::MinorFlashing);
		timer->startTimer();
//		timer->addReceiver(*this);
	}else if(currentState == States::FlashingMinDuration){
		onDeferred = true;
	}
	// else ignore event on()
}
//------------------------------------------
void CrossRoad::regulateTraffic(){
	Guard guard = tryLock();

	if(currentState == States::MajorDrive){
		setState(States::MajorYellow);
		entryMajorYellow();
		regulateTrafficDeferred = false;
		wait(Times::MajorYellow);
		timer->startTimer();
//		timer->addReceiver(*this);
	}else if(	currentState == States::MinorYellow
			||	currentState == States::MajorRedYellow
			||	currentState == States::MajorMinDuration){
		regulateTrafficDeferred = true;
		//std::cout << "CrossRoad::regulateTraffic() deferred in State: " << stateToString() << std::endl;
	}
	// else ignore event regulateTraffic
}
//------------------------------------------
void CrossRoad::off(){
	Guard guard = tryLock();

	if(currentState == States::Flashing){
		setState(States::OffMinDuration);
		entryOffMinDuration();
		offDeferred = false;
		wait(Times::OffMinDuration);
		timer->startTimer();
	}else if(currentState == States::FlashingMinDuration || currentState == States::OffMinDuration){
		offDeferred = true;
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
	case States::FlashingMinDuration:
		setState(States::Flashing);
		entryFlashing();
		timer->stopTimer();
//		timer->removeReceiver(*this);

		//handle deferred events
		if(offDeferred){ // Priority = 1
			guard.unlock();
			off();
		}
		else if(onDeferred){ // Priority = 0
			guard.unlock();
			on();
		}
		break;
	case States::OffMinDuration:
		setState(States::Off);
		entryOff();
		timer->stopTimer();
//		timer->removeReceiver(*this);

		//handle deferred events
		if(flashDeferred){
			guard.unlock();
			flash();
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

	case States::Off:
	case States::Flashing:
	default:
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
void CrossRoad::entryOff(){ // called from Ctor
	// nothing to do
}
void CrossRoad::entryOffMinDuration(){
	a1->off();
	a2->off();
	a3->off();
}
void CrossRoad::entryFlashing(){
	// do nothing
}
void CrossRoad::entryFlashingMinDuration(){
	a1->flash();
	a2->flash();
	a3->flash();
}
void CrossRoad::entryMinorFlashing(){
	a1->switchOver(); // Yellow
	a2->switchOver();
}
void CrossRoad::entryMinorYellow(){
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
	case States::OffMinDuration:
		return "OffMinDuration";
	case States::Flashing:
		return "Flashing";
	case States::FlashingMinDuration:
		return "FlashingMinDuration";
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
