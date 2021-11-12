cmake_minimum_required(VERSION 3.12)
project(TrafficLightTests)

add_executable(
  TrafficLightGTest
  test/gtest/TrafficLightReferenceTest.cpp test/gtest/TrafficLightStatePatternTest.cpp
  test/gtest/TrafficLightSwitchedTest.cpp)
target_include_directories(TrafficLightGTest PRIVATE include Mocks)
target_link_libraries(TrafficLightGTest PRIVATE gmock_main ResultManagerMock
                                               CrossRoad TrafficControlSystem)
add_test(TrafficLightGTest TrafficLightGTest)

add_executable(TrafficLightCUTE test/cute/main.cpp)
target_include_directories(TrafficLightCUTE PRIVATE include Mocks)
target_link_libraries(TrafficLightCUTE PRIVATE ResultManagerMock CrossRoad
                                               TrafficControlSystem cute::cute)
add_test(TrafficLightCUTE TrafficLightCUTE)
