/*
 * CrossRoadConfiguration.hpp
 *
 *  Created on: 29.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_CROSSROADBUILDER_HPP_
#define INCLUDE_CROSSROADBUILDER_HPP_

#include "../include/TrafficLight.hpp"
#include "../include/TimerAdapter.hpp"

#include <CrossRoad/CrossRoad.hpp>
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

namespace Demo{

class CrossRoadBuilder{
public:
	using CrossRoad = CrossRoadLib::CrossRoad;
	using TrafficLight = Demo::TrafficLight;
	using TrafficLightTimerRepo = SimplePeriodicTimer::DefaultTimerRepository<Demo::TrafficLight, 3>;
	using TrafficLightTimer = SimplePeriodicTimer::PeriodicTimerImpl<TrafficLightTimerRepo>;
	using CrossRoadTimerRepo = SimplePeriodicTimer::DefaultTimerRepository<CrossRoad, 1, CrossRoad::IntervalDuration>;

	CrossRoadBuilder()
	:
		trafficLightTimer(),
		a1("a1", trafficLightTimer),
		a2("a2", trafficLightTimer),
		a3("a3", trafficLightTimer),
		periodicTimer(),
		crossRoadTimer(periodicTimer),
		crossRoad(a1, a2, a3, crossRoadTimer)
	{}
	CrossRoad& getCrossRoad(){ return crossRoad; }
private:

	TrafficLightTimer trafficLightTimer;
	TrafficLight a1, a2, a3;

	SimplePeriodicTimer::PeriodicTimerImpl<CrossRoadTimerRepo> periodicTimer;
	Demo::TimerAdapter crossRoadTimer;

	CrossRoad crossRoad;
};

} // namespace Demo

#endif /* INCLUDE_CROSSROADBUILDER_HPP_ */
