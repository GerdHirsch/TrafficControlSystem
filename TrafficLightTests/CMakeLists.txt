cmake_minimum_required(VERSION 3.12)
project(TrafficLightTests)

add_executable(
  TrafficLightTest
  test/TrafficLightReferenceTest.cpp test/TrafficLightStatePatternTest.cpp
  test/TrafficLightSwitchedTest.cpp)
target_include_directories(TrafficLightTest PRIVATE include Mocks)
target_link_libraries(TrafficLightTest PRIVATE gmock_main ResultManagerMock
                                               CrossRoad TrafficControlSystem)
add_test(TrafficLightTest TrafficLightTest)
