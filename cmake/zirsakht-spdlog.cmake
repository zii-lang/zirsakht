option(ZIRSAKHT_USE_SPDLOG
	"Forces use of spdlog library."
	OFF
)

if(ZIRSAKHT_ENABLE_TESTS)
	set(ZIRSAKHT_USE_SPDLOG ON)
endif()

set(ZIRSAKHT_HAS_SPDLOG OFF)

if(ZIRSAKHT_USE_SPDLOG)

	if(SPDLOG_DIR)
		message(STATUS
			"Looking for `spdlog` in SPDLOG_DIR: ${SPDLOG_DIR}"
		)

		find_package(spdlog CONFIG QUIET
			PATHS "${SPDLOG_DIR}"
			NO_DEFAULT_PATH
		)
	endif()

	if(NOT spdlog_FOUND)
		find_package(spdlog CONFIG QUIET)
	endif()

	if(NOT spdlog_FOUND)
		message(STATUS
			"spdlog not found; fetching spdlog with FetchContent."
		)

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

		set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)

		FetchContent_MakeAvailable(spdlog)
		set_target_properties(spdlog
			PROPERTIES POSITION_INDEPENDENT_CODE ON
		)
	endif()

	if(TARGET spdlog::spdlog)
		set(ZIRSAKHT_HAS_SPDLOG ON)
	endif()
endif()