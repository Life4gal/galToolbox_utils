cmake_minimum_required(VERSION 3.13)

project(
		galToolbox_utils
		DESCRIPTION "utils part of galToolbox"
		HOMEPAGE_URL "https://github.com/Life4gal/galToolbox_utils"
		LANGUAGES CXX
)

set(GALTOOLBOX_MODULE_PATH cmake)
set(GALTOOLBOX_CONFIG_PATH config)

option(BUILD_AS_SHARED "build ${PROJECT_NAME} as a shared module.(otherwise, as a static module)" OFF)
option(BUILD_TEST_CASES "build ${PROJECT_NAME} test cases" ON)
option(BUILD_GOOGLETEST_PUBLIC "let googletest as a public module of ${PROJECT_NAME}." ON)
option(BUILD_FMTLIB_PUBLIC "let fmtlib as a public module of ${PROJECT_NAME}.(if std::format is not support)" ON)

set(
		${PROJECT_NAME}_SOURCE
		src/assert.cpp
)

if(${BUILD_AS_SHARED})
	message("${PROJECT_NAME} info: build ${PROJECT_NAME} as a shared module.")
	add_library(
			${PROJECT_NAME}
			SHARED
			${${PROJECT_NAME}_SOURCE}
	)
	target_compile_definitions(
			${PROJECT_NAME}
			PRIVATE
			GALTOOLBOX_NEED_EXPORT
	)
else()
	message("${PROJECT_NAME} info: build ${PROJECT_NAME} as a static module.")
	add_library(
			${PROJECT_NAME}
			STATIC
			${${PROJECT_NAME}_SOURCE}
	)
endif(${BUILD_AS_SHARED})

add_library(
		galToolbox::utils
		ALIAS
		${PROJECT_NAME}
)

if(${BUILD_TEST_CASES})
	message("${PROJECT_NAME} info: build ${PROJECT_NAME}'s test cases.")
	add_subdirectory(test)
else()
	message("${PROJECT_NAME} info: drop ${PROJECT_NAME}'s test cases.")
endif(${BUILD_TEST_CASES})

target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_options(
		${PROJECT_NAME}
		PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/std:c++latest /W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-std=c++2a -Wall -Wextra -Wpedantic -Werror>
)

include(${GALTOOLBOX_MODULE_PATH}/google-test.cmake)

if(${BUILD_GOOGLETEST_PUBLIC})
	message("${PROJECT_NAME} info: let googletest as a public module of ${PROJECT_NAME}.")
	target_link_libraries(
			${PROJECT_NAME}
			PUBLIC
			gtest_main
	)
else()
	message("${PROJECT_NAME} info: let googletest as a private module of ${PROJECT_NAME}.")
	target_link_libraries(
			${PROJECT_NAME}
			PRIVATE
			gtest_main
	)
endif(${BUILD_GOOGLETEST_PUBLIC})

include(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES(
	"
		#include <format>

		int main()
		{
			std::cout << std::format(\"hello {}!\", \"world\");
		}
	"
	COMPILER_SUPPORT_FORMAT
)

if(${COMPILER_SUPPORT_FORMAT})
	message("${PROJECT_NAME} info: current compiler ${CMAKE_CXX_COMPILER} support std::format.")
else()
	message("${PROJECT_NAME} info: current compiler ${CMAKE_CXX_COMPILER} not support std::format, use fmtlib instead now.")
	target_compile_definitions(
			${PROJECT_NAME}
			PRIVATE
			GALTOOLBOX_FMT_NOT_SUPPORT
	)
	include(${GALTOOLBOX_MODULE_PATH}/fmtlib.cmake)
	if(${BUILD_FMTLIB_PUBLIC})
		message("${PROJECT_NAME} info: build fmtlib as a public module of ${PROJECT_NAME}.")
		target_link_libraries(
				${PROJECT_NAME}
				PUBLIC
				fmt
		)
	else()
		message("${PROJECT_NAME} info: build fmtlib as a private module of ${PROJECT_NAME}.")
		target_link_libraries(
				${PROJECT_NAME}
				PRIVATE
				fmt
		)
	endif(${BUILD_FMTLIB_PUBLIC})
endif(${COMPILER_SUPPORT_FORMAT})

