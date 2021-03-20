/*
 * ResultManager.h
 *
 *  Created on: 19.03.2021
 *      Author: Gerd
 */

#ifndef RESULTMANAGER_H_
#define RESULTMANAGER_H_
#include <string>
namespace Mock {

class ResultManager {
public:
	enum States{ NoTracking, Init, Test, Finished};

	ResultManager();
	virtual ~ResultManager();
	void beginInit();
	void endInit();
	void beginTest();
	void endTest();
	void addString(std::string message);
	bool succeed() const;
private:
	States currentState = NoTracking;
	std::string expected;
	std::string result;

};

} /* namespace Mock */

#endif /* RESULTMANAGER_H_ */
