cmake_minimum_required(VERSION 3.12)
project(CrossRoad)

add_library(CrossRoad src/CrossRoad.cpp)
target_include_directories(CrossRoad PUBLIC include/)
