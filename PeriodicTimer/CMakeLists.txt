cmake_minimum_required(VERSION 3.12)
project(PeriodicTimer)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_library(PeriodicTimer INTERFACE)
target_include_directories(PeriodicTimer INTERFACE include/)
target_link_libraries(PeriodicTimer INTERFACE Threads::Threads)

add_executable(PeriodicTimerDemo src/DemoReceivers.cpp src/DemoTimer.cpp
                                 src/main.cpp)
target_link_libraries(PeriodicTimerDemo PUBLIC PeriodicTimer)
