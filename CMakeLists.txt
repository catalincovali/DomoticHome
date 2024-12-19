cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(DomoticHome)

include_directories(include)

add_executable( main
  src/main.cpp
  #.cpp files ...
)
