cmake_minimum_required(VERSION 3.12)
project(TrafficLightCUTE)

add_executable(TrafficLightCUTE src/Test.cpp)
target_include_directories(TrafficLightCUTE PRIVATE cute)
target_link_libraries(TrafficLightCUTE PRIVATE ResultManagerMock CrossRoad
                                               TrafficControlSystem)
