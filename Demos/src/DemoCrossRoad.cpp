

#include "../include/CrossRoadBuilder.hpp"
#include "../include/TrafficLight.hpp"
#include "../include/TimerAdapter.hpp"

#include <CrossRoad/CrossRoad.hpp>
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
namespace CR = CrossRoadLib;
namespace SPT = SimplePeriodicTimer;

template<class Selectors>
void printSelectors(Selectors &selectors){
	cout << "=======================" << endl;
	for(auto selector : selectors)
		cout << selector << endl;
	cout << "=======================" << endl;
}

void demoCrossRoadInteractive(){
	cout << __PRETTY_FUNCTION__ << endl;

	Demo::CrossRoadBuilder builder;
	CR::CrossRoad &crossRoad = builder.getCrossRoad();
	CR::CrossRoad::printout = true;

	string selector;
	const string selectors[] = {
			"quit", "off", "on", "flash", "regulate", "defect"
	};
	enum {quit, off, on, flash, regulate, defect};


	do{
		printSelectors(selectors);
		cout << "Select: ";
		cin >> selector;
		cout << "selector: " << selector << endl;
		if(selector == selectors[off]){
			crossRoad.off();
		} else if(selector == selectors[on]){
			crossRoad.on();
		} else if(selector == selectors[flash]){
			crossRoad.flash();
		} else if(selector == selectors[regulate]){
			crossRoad.regulateTraffic();
		} else if(selector == selectors[defect]){
			crossRoad.defect();
		} else if(selector == selectors[quit]){
			// nothing to do
		}else{
			cout << "choose one provided:" << endl;
		}

	}while(selector != selectors[quit]);

	cout << "thanks for trying this demo" << endl;



}

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

		std::cout << "===> demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		cout << "===> crossRoad.flash();" << endl;
		crossRoad.flash();

		std::cout << "===> demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		cout << "===> crossRoad.on();" << endl;
		crossRoad.on();

		std::cout << "===> demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(sleepDuration);

		cout << "===> crossRoad.regulateTraffic();" << endl;
		crossRoad.regulateTraffic();

		std::cout << "===> demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));

		cout << "===> crossRoad.flash();" << endl;
		crossRoad.flash();

		std::cout << "===> demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));

		cout << "===> crossRoad.off();" << endl;
		crossRoad.off();

		std::cout << "===> demoCrossRoad sleep " << this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}


	std::cout << "end " << __PRETTY_FUNCTION__ << std::endl;
}
