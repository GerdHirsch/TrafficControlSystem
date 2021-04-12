/*
 * runAllTests for interface/protocol Ampel
 */

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <iostream>

#include <TCS/TrafficLight.hpp>

#include "../include/ReferenceTest.h"
#include "../include/TrafficLightSwitchedTest.h"
#include "../include/TrafficLightStatePatternTest.h"
using namespace std;

using TLSwitched = TrafficLightSwitchedTest;
using TLSPTest = TrafficLightStatePatternTest;

void runAllTests(int argc, char const *argv[]){
	cout << "runAllTests()" << endl;
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(ReferenceTest::make_suite(), "ReferenceTest");
	cute::makeRunner(lis,argc,argv)(TLSwitched::make_suite(), "TrafficLightSwitchedTest");
	cute::makeRunner(lis,argc,argv)(TLSPTest::make_suite(), "TrafficLightStatePatternTest");
}

int main(int argc, char const *argv[]){

    runAllTests(argc,argv);

}



