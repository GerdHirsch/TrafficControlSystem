cmake_minimum_required(VERSION 3.12)
project(ResultManagerCUTE)

add_executable(ResultManagerCUTE src/Test.cpp)
target_include_directories(ResultManagerCUTE PRIVATE cute)
target_link_libraries(ResultManagerCUTE PRIVATE ResultManagerMock)
