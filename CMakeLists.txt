cmake_minimum_required(VERSION 3.5)

project(Bankrupt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_FILES *.cpp)

add_executable(Bankrupt ${PROJECT_FILES})
 
