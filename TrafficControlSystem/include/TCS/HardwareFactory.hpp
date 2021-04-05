/*
 * HardwareFactory.hpp
 *
 *  Created on: 05.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TCS_HARDWAREFACTORY_HPP_
#define INCLUDE_TCS_HARDWAREFACTORY_HPP_

#include <TCS/LampIP.hpp>
#include <Sensor/Sensor.h>
#include <Sensor/ListenerSingleRawPointer.h>

#include <string>

namespace TCS{

class HardwareFactory{
public:
	//--------------------------------
	using Lamp = TCS::LampIP;
	Lamp createLamp(std::string name){
		std::string ipAddress = loadIPAddressFor(std::move(name));
		return Lamp(ipAddress);
	}
	//--------------------------------
	using ObserverPolicy = SensorHersteller::ListenerSingleRawPointerPolicy;
	using Sensor = SensorHersteller::Sensor<ObserverPolicy>;

	Sensor createSensor(std::string name){
		// loadIPAddressFor(name); // just omitted in demo
		return Sensor();
	}
	//--------------------------------
private:
	std::string loadIPAddressFor(std::string name){
		// read configuration File just omitted in demo
		return name;
	}
};

} // namesapce TCS
#endif /* INCLUDE_TCS_HARDWAREFACTORY_HPP_ */
