cmake_minimum_required(VERSION 3.6)
project(WayBigWork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h FindWay.h DeikstraFW.cpp DeikstraFW.h FordFW.cpp FordFW.h)
add_executable(WayBigWork ${SOURCE_FILES})