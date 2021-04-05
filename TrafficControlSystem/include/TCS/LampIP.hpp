/*
 * LampIP.hpp
 *
 *  Created on: 05.04.2021
 *      Author: Gerd
 */

#ifndef INCLUDE_TCS_LAMPIP_HPP_
#define INCLUDE_TCS_LAMPIP_HPP_

#include "Lamp.hpp"

#include <iostream>
#include <string>

namespace TCS{

class LampIP : public Lamp{
public:

	LampIP(std::string IPAddress)
	:
		IPAddress(std::move(IPAddress)),
		state(State::off)
	{}
	void on() {
		std::cout << IPAddress << ".on() IP" << std::endl;
		state = State::on;
	}
	void off() {
		std::cout << IPAddress << ".off() IP" << std::endl;
		state = State::off;
	}
	bool isOn(){ return static_cast<bool>(state);}
private:
	std::string IPAddress;
	enum class State : bool {off=false, on=true} state;
};

} // namespace TCS


#endif /* INCLUDE_TCS_LAMPIP_HPP_ */
