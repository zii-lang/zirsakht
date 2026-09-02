cmake_minimum_required(VERSION 3.20.0)

project(zirsakht LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include(FetchContent)
include(CheckIncludeFiles)
include(GNUInstallDirs)

# -- Options --
option(ZIRSAKHT_BUILD_SHARED "Build shared library" OFF)
option(ZIRSAKHT_BUILD_STATIC "Build static library" ON)
option(ZIRSAKHT_ENABLE_TESTS "Enable unit tests" OFF)

set(zirsakht_libname "zirsakht")

set(zirsakht_cflags "")
set(zirsakht_cxxflags "")
set(zirsakht_libraries "")
set(zirsakht_defines "")
set(zirsakht_includes "")

set(zirsakht_install_objdir "${CMAKE_INSTALL_LIBDIR}")
set(zirsakht_install_incdir "${CMAKE_INSTALL_INCLUDEDIR}")

set(zirsakht_sources)
file(GLOB zirsakht_sources "src/*.cpp")

list(APPEND zirsakht_includes
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(ZIRSAKHT_BUILD_SHARED)
	list(APPEND zirsakht_build_targets "shared")
endif()

if(ZIRSAKHT_BUILD_STATIC)
	list(APPEND zirsakht_build_targets "static")
endif()

if(ZIRSAKHT_BUILD_OBJECT)
	list(APPEND zirsakht_build_targets "object")
endif()

message(STATUS "")
message(STATUS "Library Name        : ${zirsakht_libname}")
message(STATUS "CXX Compiler        : ${CMAKE_CXX_COMPILER}")
message(STATUS "Link Libraries      : ${zirsakht_libraries}")
message(STATUS "Include Directories : ${zirsakht_includes}")
message(STATUS "Defines             : ${zirsakht_defines}")
message(STATUS "")

add_library(zirsakht-static STATIC ${zirsakht_sources})
target_link_libraries(zirsakht-static PRIVATE ${zirsakht_libraries})
target_include_directories(zirsakht-static PUBLIC ${zirsakht_includes})
set_property(TARGET zirsakht-static PROPERTY OUTPUT_NAME ${zirsakht_libname})
set_property(TARGET zirsakht-static PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(zirsakht-static
	PRIVATE
		${zirsakht_defines}
		ZIRSAKHT_STATIC_LIB
)
target_compile_options(zirsakht-static
	PRIVATE
		${zirsakht_cxxflags}
		${zirsakht_cxxflags_static}
)
target_link_libraries(zirsakht-static PRIVATE ${zirsakht_libraries})
target_include_directories(zirsakht-static
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${zirsakht_install_incdir}>
)

install(
	TARGETS zirsakht-static
	EXPORT zirsakht
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if("${zirsakht_library}" STREQUAL "")
	set(zirsakht_library "zirsakht-static")
endif()

add_library(zirsakht::zirsakht ALIAS ${zirsakht_library})