if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(ZIRSAKHT_DEBUG_MODE 1)
else()
	set(ZIRSAKHT_DEBUG_MODE 0)
endif()

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/include/Z/Zirsakht/Config.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/include/Z/Zirsakht/Config.hpp
)