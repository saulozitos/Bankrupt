cmake_minimum_required(VERSION 3.5)

project(Bankrupt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -O3")

file(GLOB PROJECT_FILES *.cpp *.h *.hpp)

add_executable(Bankrupt ${PROJECT_FILES})
 
