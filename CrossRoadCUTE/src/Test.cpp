//#include "../include/CrossRoadTest.hpp"
#include "../include/RegulateTrafficDeferredTest.hpp"
#include "../include/PriorityTest.hpp"
#include "../include/DefectTest.hpp"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "../include/OperationflashTest.hpp"
#include "../include/OperationtriggerTest.hpp"
#include "../include/StartTest.hpp"

void runAllTests(int argc, char const *argv[]) {

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> listener(xmlfile.out);

	cute::makeRunner(listener,argc,argv)(StartTest::make_suite(), "StartTest");
	cute::makeRunner(listener,argc,argv)(Operation_trigger_Test::make_suite(), "Operation_trigger_Test");
	cute::makeRunner(listener,argc,argv)(Operation_flash_Test::make_suite(), "Operation_flash_Test");
	cute::makeRunner(listener,argc,argv)(RegulateTrafficDeferredTest::make_suite(), "RegulateTrafficDeferredTest");
	cute::makeRunner(listener,argc,argv)(PriorityTest::make_suite(), "PriorityTest");
	cute::makeRunner(listener,argc,argv)(DefectTest::make_suite(), "DefectTest");
}

int main(int argc, char const *argv[]) {
    runAllTests(argc, argv);
}
