#ifndef CROSSROAD_HPP_
#define CROSSROAD_HPP_

#include <PeriodicTimer/PeriodicTimer.hpp>
#include "TrafficLight.hpp"

#include <mutex>

class CrossRoad{
public:
	using Mutex = std::timed_mutex;
	using Guard = std::unique_lock<Mutex>;
	using Duration = std::chrono::milliseconds;

	CrossRoad(
			TrafficLight& a1,
			TrafficLight& a2,
			TrafficLight& a3,
			PeriodicTimer<CrossRoad>& timer);

	enum struct States{ //todo Off/FlashingMinDuration
		Off, OffMinDuration, Flashing, FlashingMinDuration, MinorFlashing,
		MinorYellow, MajorRedYellow, MajorDrive, MajorMinDuration,
		MajorYellow, MinorRedYellow, MinorDrive, Defect
	};
	enum  Times {
		OffMinDuration = 2000, FlashingMinDuration = 2000, MinorFlashing = 2000,
		MinorYellow = 1500, MajorRedYellow = 500, /*MajorDrive = 0,*/ MajorMinDuration = 5000,
		MajorYellow = 2000, MinorRedYellow = 500, MinorDrive = 5000
	};
//	enum  Times { // script timings
//		Off = 2000, Flashing = 2000, MinorFlashing = 5000,
//		MinorYellow = 3000, MajorRedYellow = 3000, /*MajorDrive = 0,*/ MajorMinDuration = 30000,
//		MajorYellow = 5000, MinorRedYellow = 2000, MinorDrive = 20000
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
	std::string stateToString()const;
	void wait(unsigned long long msDuration);
	Guard tryLock();
	//================================================
	// entry behaviors
	void entryOff();
	void entryFlashing();
	void entryMinorFlashing();
	void entryMinorYellow();
	void entryMajorRedYellow();
	void entryMajorMinDuration();
	void entryMajorDrive();
	void entryMajorYellow();
	void entryMinorRedYellow();
	void entryMinorDrive();

private: // Members
	//================================================
	//------------------------------------------------
	States currentState = States::Off;
	TrafficLight *a1, *a2, *a3;
	PeriodicTimer<CrossRoad>* timer;
	Mutex myMutex;
	//------------------------------------------------
	// defered Events
	bool regulateTrafficDeferred = false;
	bool flashDeferred = false;
};



#endif /* CROSSROAD_HPP_ */
