cmake_minimum_required(VERSION 3.12)
project(CrossRoadCUTE)

add_executable(CrossRoadCUTE src/Test.cpp)
target_include_directories(CrossRoadCUTE PRIVATE cute)
target_link_libraries(CrossRoadCUTE PRIVATE ResultManagerMock CrossRoad)
