/*
 * CrossRoadSensorAdapter.hpp
 *
 *  Created on: 05.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TCS_CROSSROADSENSORADAPTER_HPP_
#define INCLUDE_TCS_CROSSROADSENSORADAPTER_HPP_

#include <Sensor/SensorListener.h>
#include <CrossRoad/CrossRoad.hpp>

class CrossRoadSensorAdapter : public SensorHersteller::SensorListener{
public:
	using CrossRoad = CrossRoadLib::CrossRoad;
	CrossRoadSensorAdapter(CrossRoad &crossRoad) : crossRoad(&crossRoad){}
	virtual void trigger(unsigned long timestamp){
		crossRoad->regulateTraffic();
	}
private:
	CrossRoad *crossRoad;
};

#endif /* INCLUDE_TCS_CROSSROADSENSORADAPTER_HPP_ */
