/*
 * runAllTests for interface/protocol Ampel
 */

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <iostream>

//#include "../include/TrafficLightReference.hpp"
#include <TCS/TrafficLight.hpp>

#include "../include/TrafficLightReferenceTest.h"
using namespace std;


using ReferenceTest = TrafficLightReferenceTest<>;
using TCSTrafficLightTest = TrafficLightReferenceTest<TCS::TrafficLight>;

void runAllTests(int argc, char const *argv[]){
	cout << "runAllTests()" << endl;
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(ReferenceTest::make_suite(), "TrafficLightReferenceTest");
	cute::makeRunner(lis,argc,argv)(TCSTrafficLightTest::make_suite(), "TCSTrafficLightTest");
}

int main(int argc, char const *argv[]){

    runAllTests(argc,argv);

}



