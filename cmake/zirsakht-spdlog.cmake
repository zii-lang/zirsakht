option(ZIRSAKHT_USE_SPDLOG "Forces use of spdlog library." OFF)

set(ZIRSAKHT_HAS_SPDLOG OFF)

if(ZIRSAKHT_USE_SPDLOG)

	# ==========================================================================
	# Find spdlog
	# ==========================================================================

	if(SPDLOG_DIR)
		message(STATUS "Looking for `spdlog` in SPDLOG_DIR: ${SPDLOG_DIR}")

		find_package(spdlog CONFIG QUIET
			PATHS "${SPDLOG_DIR}"
			NO_DEFAULT_PATH
		)
	endif()

	# Then try the normal system/vcpkg/package-manager locations.
	if(NOT spdlog_FOUND)
		find_package(spdlog CONFIG QUIET)
	endif()

	# ==========================================================================
	# Fetch spdlog if it wasn't found
	# ==========================================================================

	if(NOT spdlog_FOUND)
		message(STATUS "spdlog not found; fetching spdlog with FetchContent.")

		include(FetchContent)

		FetchContent_Declare(
			spdlog
			GIT_REPOSITORY
			https://github.com/gabime/spdlog.git
			GIT_TAG
			v1.17.0
			GIT_SHALLOW
			TRUE
		)

		# Don't install spdlog when installing this project.
		set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)

		FetchContent_MakeAvailable(spdlog)
	endif()

	if(spdlog_FOUND)
		set(ZIRSAKHT_HAS_SPDLOG ON)
	endif()

endif()