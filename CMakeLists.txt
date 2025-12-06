cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2025
        DESCRIPTION "Advent of Code 2025 Solutions"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiling move semantics/references executables
add_executable(day1 day1/day1.cpp)
add_executable(day2 day2/day2.cpp)
add_executable(day3 day3/day3.cpp)
add_executable(day4 day4/day4.cpp)
add_executable(day5 day5/day5.cpp)
add_executable(day6 day6/day6.cpp)