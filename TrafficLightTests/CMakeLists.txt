cmake_minimum_required(VERSION 3.12)
project(TrafficLightTests)

add_library(ReferenceTrafficLight INTERFACE)
target_include_directories(ReferenceTrafficLight INTERFACE include)

add_executable(
  TrafficLightGTest
  test/gtest/TrafficLightReferenceTest.cpp
  test/gtest/TrafficLightStatePatternTest.cpp
  test/gtest/TrafficLightSwitchedTest.cpp)
target_link_libraries(
  TrafficLightGTest PRIVATE gmock_main CrossRoad TrafficControlSystem
                            ReferenceTrafficLight)
add_test(TrafficLightGTest TrafficLightGTest)

add_executable(TrafficLightCUTE test/cute/main.cpp)
target_link_libraries(
  TrafficLightCUTE PRIVATE ResultManagerMock CrossRoad ReferenceTrafficLight
                           TrafficControlSystem cute::cute)
add_test(TrafficLightCUTE TrafficLightCUTE)
