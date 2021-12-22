cmake_minimum_required(VERSION 3.12)
project(cute)

add_library(cute INTERFACE)
target_include_directories(cute INTERFACE include)
add_library(cute::cute ALIAS cute)