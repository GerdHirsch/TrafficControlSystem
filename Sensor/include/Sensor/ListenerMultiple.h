/*
 * ObserverWeakPointer.h
 *
 *  Created on: 23.07.2015
 *      Author: Gerd
 */

#ifndef LISTENERMULTIPLE_H_
#define LISTENERMULTIPLE_H_

#include "SensorListener.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace SensorHersteller{
/**
 * Responsibility: Policy, verwaltet die Observer und versendet
 * an alle die Nachrichten (fireTrigger(..)
 * @param Listener: zulässige Argumente:
 * entweder ein zu std::weak_ptr<SensorListener> kompatibler Smartpointer oder
 * einen zu SensorListener* kompatibler nativer Pointer
 *
 * Mit std::weak_ptr<SensorListener> entstehen keine
 * dangling pointer, die zerstörten Objekte müssen sich
 * nicht vorher abmelden
 */
template<class Listener>
class ListenerMultiple{
private:
	typedef std::vector<Listener> Listeners;
	typedef typename Listeners::iterator Iterator;
	Listeners listeners;

protected:
	ListenerMultiple():invalidPointers(false){}

public:
	void addSensorListener(Listener listener){
		listeners.push_back(listener);
	}
	void removeSensorListener(Listener listener){
		Iterator s = listeners.begin();
		Iterator e = listeners.end();
		Pointer p1 = getPointer(listener);

		auto predicate = [&](Listener l) ->bool {
			Pointer p2 = getPointer(l);

			if(!p2){
				invalidPointers = true; // invalid Pointer kann entfernt werden
				return false;
			}
			return p1 == p2;
		};

		if(p1){
			Iterator pos = std::find_if(s, e, predicate);

			if(pos != e)
				listeners.erase(pos);
		}
		removeInvalidPointers();
	}
//---------------------------------------------------------------------
protected:
	void fireTrigger(unsigned long timestamp){

		auto actionTrigger = [&](Listener l){
			//unsigned long timestamp = getTimestamp();
			Pointer p = getPointer(l);
			if(p) p->trigger(timestamp);
			else invalidPointers = true;
		};

		Iterator s = listeners.begin();
		Iterator e = listeners.end();
		std::for_each(s, e, actionTrigger);
		removeInvalidPointers();
	}
private:
	bool invalidPointers;
	void removeInvalidPointers(){
		if(invalidPointers){
//			std::cout <<"remove invalid Pointers" << std::endl;

			auto predicateInvalid =
					[](Listener l)->bool{ return !getPointer(l); };

			Iterator s = listeners.begin();
			Iterator pos = std::find_if(s, listeners.end(), predicateInvalid);
			while(pos != listeners.end()){
				// s == position behind pos
				s = listeners.erase(pos); // invalidates Iterators behind pos

				pos = std::find_if(s, listeners.end(), predicateInvalid);
			}
		}
		else{ /*std::cout <<"no invalid Pointers" << std::endl;*/ }

		invalidPointers = false;
	}

	typedef std::shared_ptr<SensorListener> SharedPointer;
	typedef std::weak_ptr<SensorListener> WeakPointer;

	/**
	 * getPointer(..)
	 * überladene Klassenmethode, liefert entweder einen
	 * native (raw) pointer auf einen SensorListener
	 * oder einen std::shared_ptr<SensorListener>
	 * wenn die Listener als std::weak_ptr verwaltet
	 * werden
	 */
	static std::shared_ptr<SensorListener> getPointer(WeakPointer p){
		return p.lock();
	}
	static SensorListener* getPointer(SensorListener* p){ return p; }

	typedef decltype(getPointer(Listener())) Pointer;

};

} // end namespace SensorHersteller

#endif /* LISTENERMULTIPLE_H_ */
