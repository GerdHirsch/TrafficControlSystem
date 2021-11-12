#ifndef INCLUDE_GMOCKLAMP_HPP_
#define INCLUDE_GMOCKLAMP_HPP_

#include <TCS/Lamp.hpp>
#include <gmock/gmock.h>

class GMockLamp : public Lamp {
public:
  GMockLamp() {
    ON_CALL(*this, off).WillByDefault([this]() { m_isOn = false; });
    ON_CALL(*this, on).WillByDefault([this]() { m_isOn = true; });
  }
  MOCK_METHOD(void, off, (), (override));
  MOCK_METHOD(void, on, (), (override));
  bool isOn() override { return m_isOn; };

private:
  bool m_isOn{false};
};

#endif /* INCLUDE_GMOCKLAMP_HPP_ */
