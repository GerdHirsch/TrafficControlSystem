
#include "../include/TCS/TrafficLight.hpp"
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include <iostream>
#include <chrono>

using namespace std;
using namespace TCS;
using namespace SimplePeriodicTimer;

void demoTrafficLight(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;

//	using IntervalDuration = std::chrono::milliseconds;
//	IntervalDuration sleepDuration(2500);
//
//	using TimerRepo = DefaultTimerRepository<TrafficLight, 3>;
//	TimerImpl<TimerRepo> timerImpl;
//	timerImpl.setIntervalDuration(500);
//	{
//		TrafficLight a1("a1", timerImpl), a2("a2", timerImpl);
//
//		std::cout << "a1.flash()" << std::endl;
//		a1.flash();
//		std::cout << "demoTrafficLight sleep " << this_thread::get_id() << std::endl;
//		std::this_thread::sleep_for(sleepDuration);
//
//		std::cout << "a2.flash()" << std::endl;
//		a2.flash();
//		std::cout << "demoTrafficLight sleep " << this_thread::get_id() << std::endl;
//		std::this_thread::sleep_for(sleepDuration);
//
//		std::cout << "a1.switchOver()" << std::endl;
//		a1.switchOver();
//		std::cout << "demoTrafficLight sleep " << this_thread::get_id() << std::endl;
//		std::this_thread::sleep_for(sleepDuration);
//
//		std::cout << "a2.switchOver()" << std::endl;
//		a2.switchOver();
//		std::cout << "demoTrafficLight sleep " << this_thread::get_id() << std::endl;
//		std::this_thread::sleep_for(sleepDuration);
//
//		std::cout << "a1.flash()" << std::endl;
//		a1.flash();
//		std::cout << "demoTrafficLight sleep " << this_thread::get_id() << std::endl;
//		std::this_thread::sleep_for(sleepDuration);
//	}
//	std::cout << "end block: " << __PRETTY_FUNCTION__ << std::endl;
//	std::cout << "demoTrafficLight sleep " << this_thread::get_id() << std::endl;
//	std::this_thread::sleep_for(sleepDuration);
//	std::cout << "end: " << __PRETTY_FUNCTION__ << std::endl;

}
