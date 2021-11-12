/*
 * PeriodicTimerMock.hpp
 *
 *  Created on: 21.03.2021
 *      Author: Gerd
 */

#ifndef MOCKS_GMOCKPERIODICTIMER_HPP_
#define MOCKS_GMOCKPERIODICTIMER_HPP_

#include <PeriodicTimer/PeriodicTimer.hpp>
#include <gmock/gmock.h>
#include <string>

namespace SPT = SimplePeriodicTimer;

template <class Receiver>
class GMockPeriodicTimer : public SPT::PeriodicTimer<Receiver> {
public:
  using this_type = GMockPeriodicTimer<Receiver>;
  using base_type = SPT::PeriodicTimer<Receiver>;

  using MemberFunction = typename base_type::MemberFunction;
  using IntervalDuration = unsigned long long;
  //==========================
  // Timer Interface
  //==========================
  void addReceiver(Receiver &receiver) override { this->receiver = &receiver; };
  bool hasReceiver() const { return receiver != nullptr; }
  void removeReceiver(Receiver &receiver) override {
    if (this->receiver == &receiver) {
      this->receiver = nullptr;
    }
  };
  void setCallback(this_type::MemberFunction function) override {
    this->function = function;
  };
  bool hasCallback() const { return function != nullptr; }

  MOCK_METHOD(void, setIntervalDuration, (IntervalDuration), (override));

  //==========================
  // Test Interface
  //==========================
  GMockPeriodicTimer() = default;

  void tick() {
    if (receiver && function) {
      (receiver->*function)();
    }
  }

private:
  Receiver *receiver = nullptr;
  MemberFunction function = nullptr;
};

#endif /* MOCKS_GMOCKPERIODICTIMER_HPP_ */
