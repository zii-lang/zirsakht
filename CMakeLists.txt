cmake_minimum_required(VERSION 3.20.0)

project(zcore LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(zcore_libname "zcore")

set(zcore_cflags "")
set(zcore_cxxflags "")
set(zcore_libraries "")
set(zcore_defines "")
set(zcore_includes "")

set(zcore_sources)
file(GLOB zcore_sources "src/*.cpp")

configure_file(
    ${CMAKE_SOURCE_DIR}/ZCoreConfig.hpp.in
    ${CMAKE_BINARY_DIR}/include/Z/ZCoreConfig.hpp @ONLY
)
list(APPEND zcore_includes $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
list(APPEND zcore_includes $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)

message(STATUS "")
message(STATUS "Library Name        : ${zcore_libname}")
message(STATUS "CXX Compiler        : ${CMAKE_CXX_COMPILER}")
message(STATUS "Link Libraries      : ${zcore_libraries}")
message(STATUS "Include Directories : ${zcore_includes}")
message(STATUS "Defines             : ${zcore_defines}")
message(STATUS "")