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
	/// Invariant: Operation: Red->RedYellow->Green->Yellow
	///Pre: currentState == Flashing or Off
	///Post: currentState == Off
	virtual void off() = 0; // throws ProtocolViolationException in Operation
	///Pre: currentState == Flashing or Operation
	///Post: currentState == next State: Flashing->Yellow->Red->RedYellow->Green->Yellow
	virtual void switchOver() = 0; // throws ProtocolViolationException in Off
	///Post: currentState == Flashing
	virtual void flash() = 0;
};

} // namespace CrossRoadLib

#endif /* INCLUDE_CROSSROAD_TRAFFICLIGHT_HPP_ */
