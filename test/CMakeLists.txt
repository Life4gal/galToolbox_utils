project(galToolbox_utils_test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)

set(
		${PROJECT_NAME}_SOURCE
		src/test_random.cpp
)

add_executable(
		${PROJECT_NAME}
		${${PROJECT_NAME}_SOURCE}
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message("${PROJECT_NAME} info: setting build type to 'RelWithDebInfo' as none was specified.")
	set(
			CMAKE_BUILD_TYPE RelWithDebInfo
			CACHE STRING "Choose the type of build." FORCE
	)
	set_property(
			CMAKE_BUILD_TYPE
			PROPERTY CACHE
			STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
else()
	message("${PROJECT_NAME} info: current build type is: ${CMAKE_BUILD_TYPE}")
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MDd /Zi /Ob0 /Od /RTC1 /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O0 -g -Wall -Wextra -Wpedantic -Werror>
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MD /O2 /Ob2 /DNDEBUG /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3 -DNDEBUG -Wall -Wextra -Wpedantic -Werror>
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MD /O1 /Ob1 /DNDEBUG /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Os -DNDEBUG -Wall -Wextra -Wpedantic -Werror>
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MD /Zi /O2 /Ob1 /DNDEBUG /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2 -g -DNDEBUG -Wall -Wextra -Wpedantic -Werror>
	)
else()
	message(FATAL_ERROR "${PROJECT_NAME} info: unsupported build type: ${CMAKE_BUILD_TYPE}")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		galToolbox::utils
)

# for gtest_discover_tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
