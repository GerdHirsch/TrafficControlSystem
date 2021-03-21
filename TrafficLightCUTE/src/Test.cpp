/*
 * runAllTests for interface/protocol Ampel
 */

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <iostream>

#include "../include/TrafficLightReference.hpp"
#include "../include/TrafficLightReferenceTest.h"
using namespace std;

void runAllTests(int argc, char const *argv[]){
	cout << "runAllTests()" << endl;
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(TrafficLightReferenceTest::make_suite(), "TrafficLightReferenceTest");
}

int main(int argc, char const *argv[]){

    runAllTests(argc,argv);

}



