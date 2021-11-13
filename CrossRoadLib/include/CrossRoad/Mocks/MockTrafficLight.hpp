#ifndef MOCKS_MOCKTRAFFICLIGHT_HPP_
#define MOCKS_MOCKTRAFFICLIGHT_HPP_

#include "CrossRoad/TrafficLight.hpp"
#include <Mock/ResultManager.hpp>

namespace CR = CrossRoadLib;
namespace Mock {

class MockTrafficLight : public CR::TrafficLight {
public:
  MockTrafficLight(std::string name, ResultManager &resultManager)
      : name(name), resultManager(&resultManager), state(Off) {}
  void off() override;
  void flash() override;
  void switchOver() override;

  std::string stateToString();

  std::string name;
  ResultManager *resultManager = nullptr;
  enum States { Off, Flashing, Red, RedYellow, Yellow, Green } state;
};

inline void MockTrafficLight::off() {
  //	state = Off;
  resultManager->addString(name);
  resultManager->addString(".off|");
  //	resultManager->addString(".off.");
  //	resultManager->addString(stateToString());
  //	resultManager->addString("|");
}

inline void MockTrafficLight::flash() {
  state = Flashing;
  resultManager->addString(name);
  resultManager->addString(".flash|");
}

inline void MockTrafficLight::switchOver() {
  resultManager->addString(name);
  resultManager->addString(".switchOver|");
}

inline std::string MockTrafficLight::stateToString() {
  switch (state) {
  case Off:
    return "Off";
    break;
  case Flashing:
    return "Flashing";
    break;
  case Red:
    return "Red";
    break;
  case RedYellow:
    return "RedYellow";
    break;
  case Yellow:
    return "Yellow";
    break;
  case Green:
    return "Green";
    break;
  }
}

} // namespace Mock

#endif // MOCKS_MOCKTRAFFICLIGHT_HPP_
