#include "DefectTest.hpp"
#include "OperationflashTest.hpp"
#include "OperationtriggerTest.hpp"
#include "PriorityTest.hpp"
#include "RegulateTrafficDeferredTest.hpp"
#include "StartIgnoredEventsTest.hpp"
#include "StartTest.hpp"
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>
#include <cstdlib>
#include <cute/cute.h>
#include <cute/cute_runner.h>


bool runAllTests(int argc, char const *argv[]) {

  cute::xml_file_opener xmlfile(argc, argv);
  cute::xml_listener<cute::ide_listener<>> listener(xmlfile.out);

  bool result = true;
  result &= cute::makeRunner(listener, argc, argv)(StartTest::make_suite(),
                                                   "StartTest");
  result &= cute::makeRunner(listener, argc, argv)(
      StartIgnoredEventsTest::make_suite(), "StartIgnoredEventsTest");
  result &= cute::makeRunner(listener, argc, argv)(
      Operation_trigger_Test::make_suite(), "Operation_trigger_Test");
  result &= cute::makeRunner(listener, argc, argv)(
      Operation_flash_Test::make_suite(), "Operation_flash_Test");
  result &= cute::makeRunner(listener, argc, argv)(
      RegulateTrafficDeferredTest::make_suite(), "RegulateTrafficDeferredTest");
  result &= cute::makeRunner(listener, argc, argv)(PriorityTest::make_suite(),
                                                   "PriorityTest");
  result &= cute::makeRunner(listener, argc, argv)(DefectTest::make_suite(),
                                                   "DefectTest");
  return result;
}

int main(int argc, char const *argv[]) {
  auto result = runAllTests(argc, argv);
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
