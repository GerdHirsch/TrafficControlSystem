cmake_minimum_required(VERSION 3.12)
project(Demos)

add_executable(Demo src/main.cpp src/DemoCrossRoad.cpp src/DemoTrafficLight.cpp)
target_link_libraries(Demo PUBLIC TrafficControlSystem)
