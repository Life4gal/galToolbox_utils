cmake_minimum_required(VERSION 3.13)

project(
		galToolbox_utils
		DESCRIPTION "utils part of galToolbox"
		HOMEPAGE_URL "https://github.com/Life4gal/galToolbox_utils"
		LANGUAGES CXX
)

set(
		GALTOOLBOX_LIBRARY_UTILS_HEADERS

		include/utils/assert.hpp
		include/utils/random.hpp
		include/utils/sequence_invoker.hpp
		include/utils/tuple_maker.hpp
		include/utils/concepts.hpp
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
		${PROJECT_NAME}
		INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_compile_options(
		${PROJECT_NAME}
		INTERFACE
		$<$<CXX_COMPILER_ID:MSVC>:/std:c++latest /W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-std=c++2a -Wall -Wextra -Wpedantic -Werror>
)
