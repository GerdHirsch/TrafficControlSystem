/*
 * ModelBuilder.hpp
 *
 *  Created on: 05.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TCS_MODELBUILDER_HPP_
#define INCLUDE_TCS_MODELBUILDER_HPP_

#include <TCS/CrossRoadTimerAdapter.hpp>
#include <TCS/CrossRoadSensorAdapter.hpp>

#include <TCS/LampIP.hpp>
#include <TCS/TrafficLight.hpp>
#include <CrossRoad/CrossRoad.hpp>
#include <PeriodicTimer/PeriodicTimerImpl.hpp>

namespace TCS{

template<class HardwareFactory>
class ModelBuilder{
public:
	using Factory = HardwareFactory;
	using Lamp = typename Factory::Lamp;
	using Sensor = typename Factory::Sensor;

//	using TrafficLight = Demo::TrafficLight;
	using TrafficLight = TCS::TrafficLight;
	using TrafficLightTimerRepo = SimplePeriodicTimer::DefaultTimerRepository<TrafficLight, 3>;
	using TrafficLightTimer = SimplePeriodicTimer::PeriodicTimerImpl<TrafficLightTimerRepo>;

	using CrossRoad = CrossRoadLib::CrossRoad;
	using CrossRoadTimerRepo = SimplePeriodicTimer::DefaultTimerRepository<CrossRoad, 1, CrossRoad::IntervalDuration>;
	using CrossRoadPeriodicTimer = SimplePeriodicTimer::PeriodicTimerImpl<CrossRoadTimerRepo>;
	using CrossRoadTimer = TCS::CrossRoadTimerAdapter;

	ModelBuilder(HardwareFactory hwFactory)
	:
		hwFactory(hwFactory),
		sensor(hwFactory.createSensor("sensor")),

		trafficLightTimer(),

		a1Red(hwFactory.createLamp("a1.red")),
		a1Yellow(hwFactory.createLamp("a1.yellow")),
		a1Green(hwFactory.createLamp("a1.green")),

		a1(a1Red, a1Yellow, a1Green, trafficLightTimer),

		a2Red(hwFactory.createLamp("a2.red")),
		a2Yellow(hwFactory.createLamp("a2.yellow")),
		a2Green(hwFactory.createLamp("a2.green")),

		a2(a2Red, a2Yellow, a2Green, trafficLightTimer),

		a3Red(hwFactory.createLamp("a3.red")),
		a3Yellow(hwFactory.createLamp("a3.yellow")),
		a3Green(hwFactory.createLamp("a3.green")),

		a3(a3Red, a3Yellow, a3Green, trafficLightTimer),

		periodicTimer(),
		crossRoadTimer(periodicTimer),
		crossRoad(a1, a2, a3, crossRoadTimer),
		adapter(crossRoad)
	{
		sensor.addSensorListener(&adapter);
	}
	CrossRoad& getCrossRoad(){ return crossRoad; }
	Sensor& getSensor(){ return sensor; }
private:
	HardwareFactory hwFactory;

	Sensor sensor;

	TrafficLightTimer trafficLightTimer;

	Lamp a1Red, a1Yellow, a1Green;
	TrafficLight a1;

	Lamp a2Red, a2Yellow, a2Green;
	TrafficLight a2;

	Lamp a3Red, a3Yellow, a3Green;
	TrafficLight a3;

	CrossRoadPeriodicTimer periodicTimer;
	CrossRoadTimer crossRoadTimer;

	CrossRoad crossRoad;
	CrossRoadSensorAdapter adapter;
};

} // namespace Demo

#endif /* INCLUDE_TCS_MODELBUILDER_HPP_ */
