/*
 * AmpelReference.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 * Diese Klasse repräsentiert die Referenz Implementierung
 * des Protokolls der Ampel
 */

#ifndef INCLUDE_AMPELREFERENCE_H_
#define INCLUDE_AMPELREFERENCE_H_

#include <CrossRoad/TrafficLight.hpp>
#include <TCS/Lamp.h>

namespace CR = CrossRoadLib;

class AmpelReference : public CR::TrafficLight{
public:

	AmpelReference(Lamp& red, Lamp& yellow, Lamp& green):
//		timer(timer),
		red(red), yellow(yellow), green(green)
{}
	void off(){
		red.off(); yellow.off(); green.off();
	}
	void flash(){}
	void switchOver(){}
private:
	enum AmpelState{ AUS, BLINKEND, ROT, ROTGELB, GELB, GRUEN } state;

	void doBlinken(){
		if(state != BLINKEND){
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

#endif /* INCLUDE_AMPELREFERENCE_H_ */
