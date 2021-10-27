cmake_minimum_required(VERSION 3.12)
project(PeriodicTimerCUTE)

add_executable(PeriodicTimerCUTE src/Test.cpp)
target_include_directories(PeriodicTimerCUTE PRIVATE cute)
target_link_libraries(PeriodicTimerCUTE PRIVATE PeriodicTimer)
