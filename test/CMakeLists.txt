cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES  ./src/*.cpp ./src/*.hpp ../src/*.cpp ../src/*.hpp)
list(FILTER SOURCES EXCLUDE REGEX "^.+main.cpp")

find_package(Catch2 3 REQUIRED)

add_executable(tests ${SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

