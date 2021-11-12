/*
 * runAllTests for interface/protocol Ampel
 */

#include <cstdlib>
#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/xml_listener.h>

#include <iostream>

#include <TCS/TrafficLight.hpp>

#include "TrafficLightReferenceTest.h"
#include "TrafficLightStatePatternTest.h"
#include "TrafficLightSwitchedTest.h"

using namespace std;

using TLReference = TrafficLightReferenceTest;
using TLSwitched = TrafficLightSwitchedTest;
using TLSPTest = TrafficLightStatePatternTest;

bool runAllTests(int argc, char const *argv[]) {
  cout << "runAllTests()" << endl;
  cute::xml_file_opener xmlfile(argc, argv);
  cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);

  bool result = true;
  result &= cute::makeRunner(lis, argc, argv)(TLReference::make_suite(),
                                              "TrafficLightReferenceTest");
  result &= cute::makeRunner(lis, argc, argv)(TLSwitched::make_suite(),
                                              "TrafficLightSwitchedTest");
  result &= cute::makeRunner(lis, argc, argv)(TLSPTest::make_suite(),
                                              "TrafficLightStatePatternTest");
  return result;
}

int main(int argc, char const *argv[]) {
  auto result = runAllTests(argc, argv);
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
