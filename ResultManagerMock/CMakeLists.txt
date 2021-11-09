cmake_minimum_required(VERSION 3.12)
project(ResultManagerMock)

add_library(ResultManagerMock src/ResultManager.cpp)
target_include_directories(ResultManagerMock PUBLIC include/)
