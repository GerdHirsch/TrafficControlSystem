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

namespace SensorHersteller{
/**
 * Responsibility: kommuniziert mit dem HW-Sensor, kennt die IP-Adresse und Port und
 * setzt die Nachrichten in aufrufe von Trigger um.
 */
template<class ObserverPolicy>
class Sensor : public ObserverPolicy{
public:
	Sensor():ObserverPolicy(){}

	void externalSignal(){
		this->fireTrigger(getTimestamp());
	}
private:
	static unsigned long getTimestamp(){ return 0;/*todo systime*/}

};

} // end namespace SensorHersteller

#endif /* SENSOR_H_ */
