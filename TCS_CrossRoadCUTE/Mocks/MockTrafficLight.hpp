/*
 * MockTrafficLight.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKTRAFFICLIGHT_HPP_
#define MOCKS_MOCKTRAFFICLIGHT_HPP_

#include <CrossRoad/TrafficLight.hpp>

namespace CR = CrossRoadLib;

class MockTrafficLight : public CR::TrafficLight{
public:
	void off() override;
	void flash() override;
	void switchOver() override;
};
inline
void MockTrafficLight::off(){

}
inline
void MockTrafficLight::flash(){

}
inline
void MockTrafficLight::switchOver(){

}



#endif /* MOCKS_MOCKTRAFFICLIGHT_HPP_ */
