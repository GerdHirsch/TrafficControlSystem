/*
 * MockTrafficLight.hpp
 *
 *  Created on: 18.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKTRAFFICLIGHT_HPP_
#define MOCKS_MOCKTRAFFICLIGHT_HPP_

#include <Mock/ResultManager.hpp>
#include <CrossRoad/TrafficLight.hpp>

namespace CR = CrossRoadLib;

namespace Mock{

class MockTrafficLight : public CR::TrafficLight{
public:
	MockTrafficLight(ResultManager& resultManager)
	:
		resultManager(&resultManager)
	{}
	void off() override;
	void flash() override;
	void switchOver() override;

	ResultManager *resultManager=nullptr;
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

} // namespace Mock

#endif /* MOCKS_MOCKTRAFFICLIGHT_HPP_ */
