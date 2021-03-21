/*
 * ResultManager.cpp
 *
 *  Created on: 19.03.2021
 *      Author: Gerd
 */

#include <Mock/ResultManager.hpp>

namespace Mock {

ResultManager::ResultManager()
: currentState(NoTracking), expected(), result()
{
}

ResultManager::~ResultManager() { }

void ResultManager::beginInit(){
	expected.clear();
	result.clear();
	if(currentState == NoTracking)
		currentState = Init;
}
void ResultManager::endInit(){
	if(currentState == Init)
		currentState = NoTracking;
}
void ResultManager::beginTest(){
	if(currentState == NoTracking)
		currentState = Test;
}
void ResultManager::endTest(){
	if(currentState == Test)
		currentState = Finished;
}
void ResultManager::addString(std::string message){
	switch(currentState){
	case Init:
		expected+=std::move(message);
		break;
	case Test:
		result+=std::move(message);
		break;
	case Finished:
	default: // nothing to do
		break;
	}
}
bool ResultManager::succeed() const{
	if(currentState != Finished) return false;
	else return expected == result;
}

} /* namespace Mock */
