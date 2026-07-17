cmake_minimum_required(VERSION 3.20)

project(
		VelocityEngine
		VERSION 0.1
		LANGUAGES CXX
)

# ----------------------------
# C++ configuration
# ----------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# MSVC runtime
if(MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY
			"MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()


# ----------------------------
# Build options
# ----------------------------

option(
		PRODUCTION_BUILD
		"Build production version"
		OFF
)


# ----------------------------
# Dependencies
# ----------------------------

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdParty/glfw-3.4)
add_subdirectory(thirdParty/glad)


# ----------------------------
# Sources
# ----------------------------

file(GLOB_RECURSE ENGINE_SOURCES
		CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)


add_executable(
		VelocityEngine
		${ENGINE_SOURCES}
)


# ----------------------------
# Include paths
# ----------------------------

target_include_directories(
		VelocityEngine
		PRIVATE
		include
		thirdParty
		thirdParty/stb_image
)


# ----------------------------
# Defines
# ----------------------------

target_compile_definitions(
		VelocityEngine
		PRIVATE
		GLFW_INCLUDE_NONE
		_CRT_SECURE_NO_WARNINGS
)


if(PRODUCTION_BUILD)

	target_compile_definitions(
			VelocityEngine
			PRIVATE
			PRODUCTION_BUILD=1
			DEVELOPMENT_BUILD=0
			ASSETS_PATH="./assets/"
	)

else()

	target_compile_definitions(
			VelocityEngine
			PRIVATE
			PRODUCTION_BUILD=0
			DEVELOPMENT_BUILD=1
			ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
	)

endif()



# ----------------------------
# Compiler warnings
# ----------------------------

if(MSVC)

	target_compile_options(
			VelocityEngine
			PRIVATE
			/W4
	)

else()

	target_compile_options(
			VelocityEngine
			PRIVATE
			-Wall
			-Wextra
			-Wpedantic
	)

endif()



# ----------------------------
# Optimizations
# ----------------------------

if(PRODUCTION_BUILD)

	include(CheckIPOSupported)

	check_ipo_supported(
			RESULT ipo_supported
	)

	if(ipo_supported)
		set_target_properties(
				VelocityEngine
				PROPERTIES
				INTERPROCEDURAL_OPTIMIZATION TRUE
		)
	endif()

endif()



# ----------------------------
# Windows executable
# ----------------------------

if(WIN32)

	set_target_properties(
			VelocityEngine
			PROPERTIES
			WIN32_EXECUTABLE TRUE
	)

endif()



# ----------------------------
# Linking
# ----------------------------

target_link_libraries(
		VelocityEngine
		PRIVATE
		glfw
		glad
)