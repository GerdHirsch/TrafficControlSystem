#ifndef INCLUDE_CROSSROAD_TIMER_HPP_
#define INCLUDE_CROSSROAD_TIMER_HPP_

#include <chrono>

namespace CrossRoadLib {
class CrossRoad;

class Timer {
public:
  using IntervalDuration = std::chrono::milliseconds;
  using CallbackType = void (CrossRoad::*)();

  virtual void add(CrossRoad &crossRoad) = 0;
  virtual void setCallback(CallbackType callback) = 0;
  virtual void setIntervalDuration(IntervalDuration nextInterval) = 0;
  virtual void stopTimer() = 0;
  virtual void startTimer() = 0;
};

} // namespace CrossRoadLib

#endif // INCLUDE_CROSSROAD_TIMER_HPP_
