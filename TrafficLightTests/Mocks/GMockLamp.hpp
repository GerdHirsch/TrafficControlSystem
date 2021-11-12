#ifndef INCLUDE_MOCKLAMP_HPP_
#define INCLUDE_MOCKLAMP_HPP_

#include <TCS/Lamp.hpp>
#include <gmock/gmock.h>

class MockLamp : public Lamp {
public:
  MockLamp() {
    ON_CALL(*this, off).WillByDefault([this]() { m_isOn = false; });
    ON_CALL(*this, on).WillByDefault([this]() { m_isOn = true; });
  }
  MOCK_METHOD(void, off, (), (override));
  MOCK_METHOD(void, on, (), (override));
  bool isOn() override { return m_isOn; };

private:
  bool m_isOn{false};
};

#endif /* INCLUDE_MOCKLAMP_HPP_ */
