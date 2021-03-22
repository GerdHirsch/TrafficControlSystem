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
	MockTrafficLight(std::string name, ResultManager& resultManager)
	:
		name(name),
		resultManager(&resultManager)
	{}
	void off() override;
	void flash() override;
	void switchOver() override;

	std::string name;
	ResultManager *resultManager=nullptr;
};
inline
void MockTrafficLight::off(){
	resultManager->addString(name);
	resultManager->addString(".off|");
}
inline
void MockTrafficLight::flash(){
	resultManager->addString(name);
	resultManager->addString(".flash|");
}
inline
void MockTrafficLight::switchOver(){
	resultManager->addString(name);
	resultManager->addString(".switchOver|");
}

} // namespace Mock

#endif /* MOCKS_MOCKTRAFFICLIGHT_HPP_ */
