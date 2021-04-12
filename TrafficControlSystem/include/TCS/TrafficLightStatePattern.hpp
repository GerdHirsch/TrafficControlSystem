/*
 * TrafficLightStatePattern.hpp
 *
 *  Created on: 12.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TCS_TRAFFICLIGHTSTATEPATTERN_HPP_
#define INCLUDE_TCS_TRAFFICLIGHTSTATEPATTERN_HPP_

#include <CrossRoad/TrafficLight.hpp>

namespace TCS{
class TrafficLightStatePattern : public CrossRoadLib::TrafficLight {
public:
	void flash() override {

	}
	void off() override {

	}
	void switchOver() override {

	}
};
} // namespace TCS



#endif /* INCLUDE_TCS_TRAFFICLIGHTSTATEPATTERN_HPP_ */
