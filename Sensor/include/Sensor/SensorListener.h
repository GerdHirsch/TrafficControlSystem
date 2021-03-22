/*
 * SensorListener.h
 *
 *  Created on: 16.07.2015
 *      Author: Gerd
 */

#ifndef SENSORLISTENER_H_
#define SENSORLISTENER_H_
#include <iostream>

namespace SensorHersteller{
/**
 * Responsibility: wertet die Nachrichten vom Sensor aus.
 * Abstrakter Partner von Sensor
 * @interface
 */
class SensorListener{
public:
	virtual ~SensorListener() = 0;
	virtual void trigger(unsigned long timestamp) = 0;
};

inline
SensorListener::~SensorListener(){
	//std::cout << "SensorListener::~SensorListener" << std::endl;
} // Definition needed

} // end namespace SensorHersteller
#endif /* SENSORLISTENER_H_ */
