/*
 * TrafficLight.hpp
 *
 *  Created on: 17.03.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_CROSSROAD_TRAFFICLIGHT_HPP_
#define INCLUDE_CROSSROAD_TRAFFICLIGHT_HPP_

namespace CrossRoadLib{

class TrafficLight{
public:
	virtual void off() = 0;
	virtual void switchOver() = 0;
	virtual void flash() = 0;
};

} // namespace CrossRoadLib

#endif /* INCLUDE_CROSSROAD_TRAFFICLIGHT_HPP_ */
