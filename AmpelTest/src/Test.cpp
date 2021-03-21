/*
 * runAllTests for interface/protocol Ampel
 */

#include "../include/AmpelReferenceTest.h"
#include "../include/AmpelReference.h"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <iostream>
using namespace std;

void runAllTests(int argc, char const *argv[]){
	cout << "runAllTests()" << endl;
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(AmpelReferenceTest::make_suite(), "AmpelReferenceTest");
}

int main(int argc, char const *argv[]){

    runAllTests(argc,argv);

}



