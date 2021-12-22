cmake_minimum_required(VERSION 3.12)
project(TrafficControlSystem)

add_library(TrafficControlSystem INTERFACE)
target_include_directories(TrafficControlSystem INTERFACE include/)
target_link_libraries(TrafficControlSystem INTERFACE Sensor CrossRoad
                                                     PeriodicTimer)

add_executable(playground src/main.cpp)
target_link_libraries(playground PUBLIC TrafficControlSystem)
