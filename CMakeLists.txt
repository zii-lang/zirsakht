cmake_minimum_required(VERSION 3.20.0)

project(zcore LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include(FetchContent)
include(CheckIncludeFiles)
include(GNUInstallDirs)

# -- Options --
option(ZCORE_BUILD_SHARED "Build shared library" OFF) # TODO: NOT YET IMPLEMENTED
option(ZCORE_BUILD_STATIC "Build static library" ON)
option(ZCORE_BUILD_OBJECT "Build object library" OFF) # TODO: NOT YET IMPLEMENTED
option(ZCORE_ENABLE_TESTS "Enable unit tests" OFF) # TODO: NOT YET IMPLEMENTED

set(zcore_libname "zcore")

set(zcore_cflags "")
set(zcore_cxxflags "")
set(zcore_libraries "")
set(zcore_defines "")
set(zcore_includes "")

set(zcore_install_objdir "${CMAKE_INSTALL_LIBDIR}")
set(zcore_install_incdir "${CMAKE_INSTALL_INCLUDEDIR}")

set(zcore_sources)
file(GLOB zcore_sources "src/*.cpp")

list(APPEND zcore_includes $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if(ZCORE_BUILD_SHARED)
	list(APPEND zcore_build_targets "shared")
endif()

if(ZCORE_BUILD_STATIC)
	list(APPEND zcore_build_targets "static")
endif()

if(ZCORE_BUILD_OBJECT)
	list(APPEND zcore_build_targets "object")
endif()

message(STATUS "")
message(STATUS "Library Name        : ${zcore_libname}")
message(STATUS "CXX Compiler        : ${CMAKE_CXX_COMPILER}")
message(STATUS "Link Libraries      : ${zcore_libraries}")
message(STATUS "Include Directories : ${zcore_includes}")
message(STATUS "Defines             : ${zcore_defines}")
message(STATUS "")

add_library(zcore-static STATIC ${zcore_sources})
target_link_libraries(zcore-static PRIVATE ${zcore_libraries})
target_include_directories(zcore-static PUBLIC ${zcore_includes})
set_property(TARGET zcore-static PROPERTY OUTPUT_NAME ${zcore_libname})
set_property(TARGET zcore-static PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(zcore-static PRIVATE ${zcore_defines} ZCORE_STATIC_LIB)
target_compile_options(zcore-static PRIVATE ${zcore_cxxflags} ${zcore_cxxflags_static})
target_link_libraries(zcore-static PRIVATE ${zcore_libraries})
target_include_directories(zcore-static PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${zcore_install_incdir}>
)

install(TARGETS zcore-static EXPORT zcore ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if("${zcore_library}" STREQUAL "")
    set(zcore_library "zcore-static")
endif()

add_library(zcore::zcore ALIAS ${zcore_library})