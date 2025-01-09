cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(DomoticHome)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable( main
  src/main.cpp
  src/Time.cpp
  src/Device.cpp
  src/CyclicDevice.cpp
  src/ManualDevice.cpp
  src/DeviceManager.cpp
  src/UserInterface.cpp
  src/Logger.cpp
  #.cpp files ...
)
