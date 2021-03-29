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
	CR::CrossRoad& getCrossRoad(){ return crossRoad; }
private:
	using TrafficLightTimerRepo = SPT::DefaultTimerRepository<Demo::TrafficLight, 3>;
	using CrossRoadTimerRepo = SPT::DefaultTimerRepository<CR::CrossRoad, 1, CR::CrossRoad::IntervalDuration>;

	SPT::PeriodicTimerImpl<TrafficLightTimerRepo> trafficLightTimer;

	Demo::TrafficLight a1, a2, a3;

	SPT::PeriodicTimerImpl<CrossRoadTimerRepo> periodicTimer;
	Demo::TimerAdapter crossRoadTimer;

	CR::CrossRoad crossRoad;
};

} // namespace Demo

#endif /* INCLUDE_CROSSROADBUILDER_HPP_ */
