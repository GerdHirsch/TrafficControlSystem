cmake_minimum_required(VERSION 3.12)
include(FetchContentHelper)

FetchContentAndPopulate(
  PeriodicTimerRepo
  GIT_REPOSITORY https://github.com/GerdHirsch/PeriodicTimer.git
  GIT_TAG master)

set(gtest_force_shared_crt ON)
FetchContentAndPopulate(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0)
