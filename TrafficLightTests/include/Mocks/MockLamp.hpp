#ifndef INCLUDE_MOCKLAMP_HPP_
#define INCLUDE_MOCKLAMP_HPP_

#include <Mock/ResultManager.hpp>
#include <TCS/Lamp.hpp>
#include <string>

class MockLamp : public Lamp {
public:
  MockLamp(std::string name, Mock::ResultManager &rm)
      : rm(rm), name(name), an(false) {}

  void on() {
    an = true;
    rm.addString(name + ".on | ");
  }
  void off() {
    an = false;
    rm.addString(name + ".off | ");
  }
  bool isOn() { return an; }

private:
  Mock::ResultManager &rm;
  std::string name;
  bool an;
};

#endif /* INCLUDE_MOCKLAMP_HPP_ */
