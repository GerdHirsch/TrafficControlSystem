/*
 * ObserverSingleRawPointer.h
 *
 *  Created on: 23.07.2015
 *      Author: Gerd
 */

#ifndef LISTENERSINGLERAWPOINTER_H_
#define LISTENERSINGLERAWPOINTER_H_

#include "SensorListener.h"

namespace SensorHersteller{


class ListenerSingleRawPointerPolicy{
public:
	typedef SensorListener* Listener;
	ListenerSingleRawPointerPolicy():listener(nullptr){}

	void addSensorListener(Listener l){
		listener = l;
	}
	void removeSensorListener(Listener l){
		if(listener == l)
			listener = 0;
	}
protected:
	Listener listener;
	void fireTrigger(unsigned long timestamp){
		if(listener){
			listener->trigger(timestamp);
		}
	}
};


}//end namespace SensorHersteller

#endif /* LISTENERSINGLERAWPOINTER_H_ */
