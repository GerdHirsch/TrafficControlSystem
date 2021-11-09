cmake_minimum_required(VERSION 3.12)

include(FetchContent)
# TODO: Change URL to upstream repo, once merged
FetchContent_Declare(
    PeriodicTimerRepo
    GIT_REPOSITORY https://github.com/GerdHirsch/PeriodicTimer.git
    GIT_TAG master
)

FetchContent_GetProperties(PeriodicTimerRepo)
if(NOT periodictimerrepo_POPULATED)
  FetchContent_Populate(PeriodicTimerRepo)
  add_subdirectory(${periodictimerrepo_SOURCE_DIR} ${periodictimerrepo_BINARY_DIR})
endif()
