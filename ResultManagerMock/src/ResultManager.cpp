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
	if(currentState == Init){
		expected.append(std::move(message));
	}else if(currentState == Test){
		result.append(std::move(message));
	}
}
bool ResultManager::succeed() const{
	return expected == result;
}

} /* namespace Mock */
