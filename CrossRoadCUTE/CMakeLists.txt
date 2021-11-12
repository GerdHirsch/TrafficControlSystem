cmake_minimum_required(VERSION 3.12)
project(CrossRoadCUTE)

add_executable(CrossRoadCUTE src/Test.cpp)
target_link_libraries(CrossRoadCUTE PRIVATE ResultManagerMock CrossRoad cute::cute)
add_test(TrafficLightCUTE TrafficLightCUTE)
