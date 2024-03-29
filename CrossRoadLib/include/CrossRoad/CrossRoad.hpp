#ifndef CROSSROAD_HPP_
#define CROSSROAD_HPP_

#include "Timer.hpp"
#include "TrafficLight.hpp"
#include <mutex>

namespace CrossRoadLib {

class CrossRoad {
public:
  using Mutex = std::timed_mutex;
  using Guard = std::unique_lock<Mutex>;
  using IntervalDuration = std::chrono::milliseconds;
  CrossRoad(TrafficLight &a1, TrafficLight &a2, TrafficLight &a3, Timer &timer);
  //			SPT::PeriodicTimer<CrossRoad>& timer);
  // Move
  CrossRoad(CrossRoad &&);
  CrossRoad &operator=(CrossRoad &&);
  // on/off output
  static bool printout;

  enum struct States {
    Off,
    OffMinDuration,
    Flashing,
    FlashingMinDuration,
    MinorFlashing,
    MinorYellow,
    MajorRedYellow,
    MajorDrive,
    MajorMinDuration,
    MajorYellow,
    MinorRedYellow,
    MinorDrive,
    Defect
  };
  enum Times {
    OffMinDuration = 2000,
    FlashingMinDuration = 2000,
    MinorFlashing = 2000,
    RedYellow = 500,
    MinorYellow = 1500,
    /*MajorDrive = 0,*/ MajorMinDuration = 5000,
    MajorYellow = 2000,
    MinorDrive = 5000
  };
  //	enum  Times { // script timings
  //		Off = 2000, Flashing = 2000, MinorFlashing = 5000,
  //		MinorYellow = 3000, MajorRedYellow = 3000, /*MajorDrive = 0,*/
  // MajorMinDuration = 30000, 		MajorYellow = 5000, MinorRedYellow =
  // 2000, MinorDrive = 20000
  //	};
  //================================================
  // public Interface
  //================================================
  void flash();
  void on();
  void regulateTraffic();
  void off();
  void defect();

private:
  //================================================
  // Internal operations
  void setState(States state);
  void trigger();
  std::string stateToString() const;
  void wait(unsigned long long msDuration);
  //================================================
  // entry behaviors
  void entryDefect();
  void entryOff();
  void entryOffMinDuration();
  void entryFlashing();
  void entryFlashingMinDuration();
  void entryMinorFlashing();
  void exitMinorFlashing();
  void entryMinorYellow();
  void entryMajorRedYellow();
  void entryMajorMinDuration();
  void entryMajorDrive();
  void entryMajorYellow();
  void entryMinorRedYellow();
  void entryMinorDrive();

private: // Members
  //================================================
  States currentState = States::Off;
  TrafficLight *a1, *a2, *a3;
  //	SPT::PeriodicTimer<CrossRoad>* timer;
  Timer *timer = nullptr;
  Mutex myMutex;
  //------------------------------------------------
  // defered Events
  bool regulateTrafficDeferred = false;
  bool flashDeferred = false;
  bool offDeferred = false;
  bool onDeferred = false;
};

} // namespace CrossRoadLib

#endif /* CROSSROAD_HPP_ */
