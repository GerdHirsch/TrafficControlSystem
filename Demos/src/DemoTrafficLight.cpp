
#include <TCS/TrafficLight.hpp>
#include <TCS/HardwareFactory.hpp>

#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include <iostream>
#include <chrono>

using namespace std;
using namespace TCS;
using namespace SimplePeriodicTimer;

void demoTrafficLight(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	using Factory = TCS::HardwareFactory;

	using TrafficLight = TCS::TrafficLight;
	using TrafficLightTimerRepo = SimplePeriodicTimer::DefaultTimerRepository<TrafficLight, 2>;
	using TrafficLightTimer = SimplePeriodicTimer::PeriodicTimerImpl<TrafficLightTimerRepo>;

	std::chrono::milliseconds sleepDuration(2000);

	{
		TrafficLightTimer timer;
		timer.setIntervalDuration(500);

		Factory factory;
		auto a1red		= factory.createLamp("a1.red");
		auto a1yellow	= factory.createLamp("a1.yellow");
		auto a1green		= factory.createLamp("a1.green");
		TrafficLight a1(a1red, a1yellow, a1green, timer);

		auto a2red		= factory.createLamp("a2.red");
		auto a2yellow	= factory.createLamp("a2.yellow");
		auto a2green		= factory.createLamp("a2.green");
		TrafficLight a2(a2red, a2yellow, a2green, timer);


		std::cout << "=== a1.flash()" << std::endl;
		a1.flash();
		std::cout << "=== demoTrafficLight sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		std::cout << "=== a2.flash()" << std::endl;
		a2.flash();
		std::cout << "=== demoTrafficLight sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		std::cout << "=== a1.switchOver()" << std::endl;
		a1.switchOver();
		std::cout << "=== demoTrafficLight sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		std::cout << "=== a1.switchOver()" << std::endl;
		a1.switchOver();
		std::cout << "=== demoTrafficLight sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		std::cout << "=== a1.flash()" << std::endl;
		a1.flash();
		std::cout << "=== a2.flash()" << std::endl;
		a2.flash();
		std::cout << "=== demoTrafficLight sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);
		std::cout << "=== a1.off()" << std::endl;
		a1.off();
		std::cout << "=== a2.off()" << std::endl;
		a2.off();
		std::cout << "=== demoTrafficLight sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(2 * sleepDuration);
	}
	std::cout << "=== end block: " << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "=== demoTrafficLight 2 * sleep " << this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(sleepDuration);
	std::cout << "=== end: " << __PRETTY_FUNCTION__ << std::endl;

}
