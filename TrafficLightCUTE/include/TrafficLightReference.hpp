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

#include <CrossRoad/TrafficLight.hpp>
#include <TCS/Lamp.h>

namespace CR = CrossRoadLib;

class TrafficLightReference : public CR::TrafficLight{
public:
	enum AmpelState{ Off, Flashing, Red, RedYellow, Yellow, Green} state;

	TrafficLightReference(Lamp& red, Lamp& yellow, Lamp& green):
		state(Off),
//		timer(timer),
		red(red), yellow(yellow), green(green)
{
		entryOff();
}
	void off(){
		if(state == Flashing){
			state = Off; // transition
			entryOff();
		}//else Todo handle ProtocolViolation
	}
	void flash(){
			state = Flashing;
	}
	void switchOver(){}
private:
	void entryOff(){
		allLampsOff();
	}
	void allLampsOff(){
		red.off(); yellow.off(); green.off();
	}

	void doFlashing(){
		if(state != Flashing){
//			timer.stop(this);
		}else if(yellow.isOn()){
			yellow.off();
		} else{
			yellow.on();
		}
	}
//	Timer timer;
	Lamp &red, &yellow, &green;
};

#endif /* INCLUDE_TRAFFICLIGHTREFERENCE_HPP_ */
