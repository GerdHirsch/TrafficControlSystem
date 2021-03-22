/*
 * AmpelReference.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 * Diese Klasse repräsentiert die Referenz Implementierung
 * des Protokolls der Ampel
 */

#ifndef INCLUDE_TRAFFICLIGHTREFERENCE_HPP_
#define INCLUDE_TRAFFICLIGHTREFERENCE_HPP_

#include <PeriodicTimer/PeriodicTimer.hpp>
#include <CrossRoad/TrafficLight.hpp>
#include <TCS/Lamp.h>

namespace CR = CrossRoadLib;
namespace SPT = SimplePeriodicTimer;

class TrafficLightReference : public CR::TrafficLight{
public:
	enum AmpelState{ Off, Flashing, Red, RedYellow, Yellow, Green} state;
	using this_type = TrafficLightReference;

	TrafficLightReference(Lamp& red, Lamp& yellow, Lamp& green, SPT::PeriodicTimer<this_type>& timer):
		state(Off),
		timer(&timer),
		red(red), yellow(yellow), green(green)
{
		entryOff();
		this->timer->setCallback(&this_type::doFlashing);
}
	void off(){
		if(state == Flashing){
			state = Off; // transition
			entryOff();
		}//else Todo handle ProtocolViolation
	}
	void flash(){
		if(state != Flashing){
			state = Flashing;
			entryFlashing();
			timer->addReceiver(*this);
		}
	}
	void switchOver(){
		switch(state){
		case Red:
			state = RedYellow;
			entryRedYellow();
			break;
		case RedYellow:
			state = Green;
			entryGreen();
			break;
		case Green:
			state = Yellow;
			entryYellow();
			break;
		case Yellow:
			state = Red;
			entryRed();
			break;
		case Flashing:
			state = Yellow;
			entryYellow();
			break;
		case Off:
		default:
			// throw ProtocolViolationException;
			break;
		}
	}
private:
	void entryOff(){
		allLampsOff();
	}
	void entryFlashing(){
		allLampsOff();
	}
	void entryRed(){
		red.on(); yellow.off(); green.off();
	}
	void entryRedYellow(){
		red.on(); yellow.on(); green.off();
	}
	void entryGreen(){
		red.off(); yellow.off(); green.on();
	}
	void entryYellow(){
		red.off(); yellow.on(); green.off();
	}
	void allLampsOff(){
		red.off(); yellow.off(); green.off();
	}

	void doFlashing(){
		if(state != Flashing){
			timer->removeReceiver(*this);
		}else if(yellow.isOn()){
			yellow.off();
		} else{
			yellow.on();
		}
	}
	SPT::PeriodicTimer<this_type>* timer;
	Lamp &red, &yellow, &green;
};

#endif /* INCLUDE_TRAFFICLIGHTREFERENCE_HPP_ */
