# This CMakeLists.txt is intended to be included through add_subdirectory().
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	message(FATAL_ERROR
		"libzirsakht_tests must be included as a subdirectory of the root project "
		"using add_subdirectory()."
	)
endif()

project(libzirsakht_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================================
# Zirsakht library
# ============================================================================

if(ZIRSAKHT_BUILD_STATIC)
	set(ZIRSAKHT_TESTS_ZIRSAKHT_TARGET zirsakht::static)
elseif(ZIRSAKHT_BUILD_SHARED)
	set(ZIRSAKHT_TESTS_ZIRSAKHT_TARGET zirsakht::shared)
else()
	message(FATAL_ERROR
		"libzirsakht_tests requires ZIRSAKHT_BUILD_STATIC or ZIRSAKHT_BUILD_SHARED "
		"to be enabled."
	)
endif()

if(NOT TARGET ${ZIRSAKHT_TESTS_ZIRSAKHT_TARGET})
	message(FATAL_ERROR
		"Expected Zirsakht target '${ZIRSAKHT_TESTS_ZIRSAKHT_TARGET}' does not exist."
	)
endif()

# ============================================================================
# GoogleTest
# ============================================================================

# First try an explicitly supplied GTEST_DIR.
if(GTEST_DIR)
	message(STATUS "Looking for GoogleTest in GTEST_DIR: ${GTEST_DIR}")

	find_package(GTest CONFIG QUIET
		PATHS "${GTEST_DIR}"
		NO_DEFAULT_PATH
	)
endif()

# Then try the normal system/vcpkg/package-manager locations.
if(NOT GTest_FOUND)
	find_package(GTest CONFIG QUIET)
endif()

# Also allow CMake's FindGTest module to locate system installations
# that don't provide a GTestConfig.cmake.
if(NOT GTest_FOUND)
	find_package(GTest QUIET)
endif()

# ============================================================================
# Fetch GoogleTest if it wasn't found
# ============================================================================

if(NOT GTest_FOUND)
	message(STATUS "GoogleTest not found; fetching GoogleTest with FetchContent.")

	include(FetchContent)

	FetchContent_Declare(
		googletest
		GIT_REPOSITORY
		https://github.com/google/googletest.git
		GIT_TAG
		v1.18.0
		GIT_SHALLOW
		TRUE
	)

	# Don't install GoogleTest when installing this project.
	set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

	FetchContent_MakeAvailable(googletest)
endif()

# ============================================================================
# Tests
# ============================================================================

file(GLOB_RECURSE test_sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(libzirsakht_tests
	${test_sources}
)

target_link_libraries(libzirsakht_tests
	PRIVATE
		${ZIRSAKHT_TESTS_ZIRSAKHT_TARGET}
		GTest::gtest
		GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(libzirsakht_tests)