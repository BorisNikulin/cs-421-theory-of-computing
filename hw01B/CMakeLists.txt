cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(HW1B LANGUAGES C CXX)

# Check to see if Doxygen is installed on the system and detectable by CMake
find_package(Doxygen)

# Defines a build option, controllable by the builder, deciding whether
# the build should be configured to produce documentation or not.
# Defaults to building docs only if Doxygen is found.
option(BUILD_DOCUMENTATION "Build Doxygen documentation" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
	if(DOXYGEN_FOUND)
		# Preprocess the Doxyfile.in file to replace CMake placeholders with
		# their final values
		set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
		set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)

		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
		message("-- Doxygen build enabled")

		# Define build system target (e.g. make docs) to run Doxygen using the
		# generated Doxyfile.
		add_custom_target(docs ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
			COMMENT "Generating API docs with Doxygen"
			VERBATIM
		)
	else()
		message(FATAL_ERROR
			"Doxygen generation requested but package was not found"
		)
	endif()
endif()

add_library(lang SHARED)
target_include_directories(lang PUBLIC include/)
target_sources(lang
	PRIVATE
		src/binary_recognizer.cpp
		src/generator_util.cpp
)
target_compile_features(lang PUBLIC cxx_std_11)

add_executable(hw1b)
target_sources(hw1b
	PUBLIC
		app/main.cpp
)
target_link_libraries(hw1b PUBLIC lang)

add_executable(hw1b-recognizer)
target_sources(hw1b-recognizer
	PUBLIC
		app/recognizer.cpp
)
target_link_libraries(hw1b-recognizer PUBLIC lang)

add_executable(hw1b-generator)
target_sources(hw1b-generator
	PUBLIC
		app/generator.cpp
)
target_link_libraries(hw1b-generator PUBLIC lang)
