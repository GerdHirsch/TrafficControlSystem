#include "../include/CrossRoadTest.hpp"

#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void runAllTests(int argc, char const *argv[]) {

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> listener(xmlfile.out);

	cute::makeRunner(listener,argc,argv)(CrossRoadTest::make_suite(), "CrossRoadTest");

}

int main(int argc, char const *argv[]) {
    runAllTests(argc, argv);
}
