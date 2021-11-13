cmake_minimum_required(VERSION 3.12)
project(CrossRoad)

add_library(CrossRoad src/CrossRoad.cpp)
target_include_directories(CrossRoad PUBLIC include/)

add_executable(CrossRoadCUTE test/cute/main.cpp)
target_link_libraries(CrossRoadCUTE PRIVATE ResultManagerMock CrossRoad
                                            cute::cute)
add_test(CrossRoadCUTE CrossRoadCUTE)
