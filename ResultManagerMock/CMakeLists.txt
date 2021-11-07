cmake_minimum_required(VERSION 3.12)
project(ResultManagerMock)

add_library(ResultManagerMock src/ResultManager.cpp)
target_include_directories(ResultManagerMock PUBLIC include/)

add_executable(ResultManagerTest test/ResultManagerTest.cpp)
target_link_libraries(ResultManagerTest PRIVATE gmock_main ResultManagerMock)
add_test(ResultManagerTest ResultManagerTest)
