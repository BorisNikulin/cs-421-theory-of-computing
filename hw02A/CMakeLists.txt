cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(HW2A
	VERSION 0.1.0.0
	LANGUAGES CXX
	DESCRIPTION "Practice with multidimensional arrays"
)

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


add_executable(hw2a)
target_sources(hw2a
	PUBLIC
		mat.cpp
)

configure_file(${PROJECT_SOURCE_DIR}/lines.txt ${PROJECT_BINARY_DIR}/lines.txt COPYONLY)
