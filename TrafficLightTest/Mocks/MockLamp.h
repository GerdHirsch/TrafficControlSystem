/*
 * MockLampe.h
 *
 *  Created on: 26.11.2017
 *      Author: Gerd
 */

#ifndef MOCKS_MOCKLAMP_H_
#define MOCKS_MOCKLAMP_H_

#include <TCS/Lamp.h>

//#include "ResultManager.h"
#include <Mock/ResultManager.hpp>
#include <string>

class MockLamp : public Lamp{
public:
	MockLamp(std::string name, Mock::ResultManager& rm): rm(rm), name(name), an(false){}

	void on(){
		an = true;
		rm.addString(name + ".on | ");
	}
	void off(){
		an = false;
		rm.addString(name + ".off | ");
	}
	bool isOn() { return an; }
private:
	Mock::ResultManager& rm;
	std::string name;
	bool an;
};

#endif /* MOCKS_MOCKLAMP_H_ */
