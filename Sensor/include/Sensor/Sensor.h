/*
 * Sensor.h
 *
 *  Created on: 16.07.2015
 *      Author: Gerd
 */

#ifndef SENSOR_H_
#define SENSOR_H_


#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>

namespace SensorHersteller{
/**
 * Responsibility: kommuniziert mit dem HW-Sensor, kennt die IP-Adresse und Port und
 * setzt die Nachrichten in aufrufe von Trigger um.
 */
template<class ObserverPolicy>
class Sensor : public ObserverPolicy{
public:
	using this_type = Sensor<ObserverPolicy>;
	Sensor():ObserverPolicy(){}

	void externalSignal(){
		this->fireTrigger(this_type::getTimestamp());
	}
private:
	static unsigned long getTimestamp(){
		return std::chrono::steady_clock::now().time_since_epoch().count();
	}

};

} // end namespace SensorHersteller

#endif /* SENSOR_H_ */
