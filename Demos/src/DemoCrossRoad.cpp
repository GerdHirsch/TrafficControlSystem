
#include "../include/TrafficLight.hpp"
#include "../include/TimerAdapter.hpp"

#include <CrossRoad/CrossRoad.hpp>
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include <iostream>
#include <chrono>

using namespace std;
namespace CR = CrossRoadLib;
namespace SPT = SimplePeriodicTimer;

void demoCrossRoad(){
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	// configure demoCrossRoad
	using IntervalDuration = std::chrono::milliseconds;
	IntervalDuration sleepDuration(2500);
	{
		// ---------- configure TrafficLights
		cout << "configure TrafficLights" << endl;
		using TrafficLightTimerRepo = SPT::DefaultTimerRepository<Demo::TrafficLight, 3>;
		SPT::PeriodicTimerImpl<TrafficLightTimerRepo> trafficLightTimer;

		Demo::TrafficLight a1("a1", trafficLightTimer);
		Demo::TrafficLight a2("a2", trafficLightTimer);
		Demo::TrafficLight a3("a3", trafficLightTimer);

		// ---------- configure CrossRoad
		cout << "configure CrossRoad" << endl;
		using CrossRoadTimerRepo = SPT::DefaultTimerRepository<CR::CrossRoad, 1, CR::CrossRoad::IntervalDuration>;
		SPT::PeriodicTimerImpl<CrossRoadTimerRepo> periodicTimer;
		Demo::TimerAdapter crossRoadTimer(periodicTimer);

		CR::CrossRoad crossRoad(a1, a2, a3, crossRoadTimer);

		std::cout << "demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		cout << "crossRoad.flash();" << endl;
		crossRoad.flash();

		std::cout << "demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		cout << "crossRoad.on();" << endl;
		crossRoad.on();

		std::cout << "demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		cout << "crossRoad.regulateTraffic();" << endl;
		crossRoad.regulateTraffic();

		std::cout << "demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));

		cout << "crossRoad.flash();" << endl;
		crossRoad.flash();

		std::cout << "demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));

		cout << "crossRoad.off();" << endl;
		crossRoad.off();

		std::cout << "demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);
	}


	std::cout << "end " << __PRETTY_FUNCTION__ << std::endl;
}
