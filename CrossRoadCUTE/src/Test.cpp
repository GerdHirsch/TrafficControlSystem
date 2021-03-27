//#include "../include/CrossRoadTest.hpp"
#include "../include/FlashDeferredTest.hpp"
#include "../include/RegulateTrafficDeferredTest.hpp"
#include "../include/PriorityTest.hpp"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "../include/StartTest.hpp"
#include "../include/TriggerTest.hpp"

void runAllTests(int argc, char const *argv[]) {

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> listener(xmlfile.out);

	cute::makeRunner(listener,argc,argv)(StartTest::make_suite(), "StartTest");
	cute::makeRunner(listener,argc,argv)(TriggerTest::make_suite(), "TriggerTest");
	cute::makeRunner(listener,argc,argv)(FlashDeferredTest::make_suite(), "FlashDeferredTest");
	cute::makeRunner(listener,argc,argv)(RegulateTrafficDeferredTest::make_suite(), "RegultatTrafficDeferredTest");
	cute::makeRunner(listener,argc,argv)(PriorityTest::make_suite(), "PriorityTest");
}

int main(int argc, char const *argv[]) {
    runAllTests(argc, argv);
}
