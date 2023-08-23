cmake_minimum_required(VERSION 3.1)

# Specify compilers
if ("${CMAKE_C_COMPILER}" STREQUAL "")
    set(CMAKE_C_COMPILER clang-10 CACHE INTERNAL "")
    message(STATUS "No C compiler was specified. Setting to ${CMAKE_C_COMPILER}")
endif()
if ("${CMAKE_CXX_COMPILER}" STREQUAL "")
    set(CMAKE_CXX_COMPILER clang++-10 CACHE INTERNAL "")
    message(STATUS "No C++ compiler was specified. Setting to ${CMAKE_CXX_COMPILER}")
endif()

# Name of the project
project(Multigame)

# Specify linker flags - set CMAKE_CURRENT_BINARY_DIR to append the current build directory
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'" )
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'" )

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

# Check if the build directory starts with build* prefix
if(NOT ${CMAKE_CURRENT_BINARY_DIR} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/build*")
    message(FATAL_ERROR "\n CMake needs to be run in a directory with prefix /build*")
endif()

# Output compiler Information and build type
message(STATUS "====== Current compiler is: ${CMAKE_CXX_COMPILER} ======")
message(STATUS "====================================")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    message(STATUS "No selected build type")
    message(STATUS "Setting to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
else()
    message(STATUS "Selected build type is ${CMAKE_BUILD_TYPE}")
endif()
message(STATUS "====================================")

# Get all source files and headers
file(GLOB SOURCES
    main_app/*.h
    main_app/*.cpp
    main_app/app_select/*.h
    main_app/app_select/*.cpp
    main_app/applications/*.h
    main_app/applications/*.cpp
    main_app/applications/roulette/*.h
    main_app/applications/roulette/*.cpp
    debug/*.h
    debug/*.cpp
    main.cpp)

# Create executable PROJECT_NAME
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify C++14 as the standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# Add include directories
set(MULTIGAME_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBS ${MULTIGAME_ROOT_DIR}/libs)
set(INTERNAL_DIRS
    ${MULTIGAME_ROOT_DIR}
    ${MULTIGAME_ROOT_DIR}/debug
    ${MULTIGAME_ROOT_DIR}/main_app
    ${MULTIGAME_ROOT_DIR}/main_app/app_select
    ${MULTIGAME_ROOT_DIR}/main_app/applications
    ${MULTIGAME_ROOT_DIR}/main_app/applications/roulette)
set(LIBS_INCLUDE_DIRS
    ${LIBS}
    ${LIBS}/glad
    ${LIBS}/glm
    ${LIBS}/imgui
    ${LIBS}/KHR
    ${LIBS}/rapidjson
    ${LIBS}/shader
    ${LIBS}/spdlog
    ${LIBS}/stb_image)
include_directories(${INTERNAL_DIRS})
include_directories(${LIBS_INCLUDE_DIRS})

#find required libraries
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

#add library glad
add_library(Glad ${LIBS}/glad/glad.h ${LIBS}/glad.c)

#add library imgui
file(GLOB IMGUI_SOURCES ${LIBS}/imgui/*.h ${LIBS}/imgui/*.cpp)
add_library(ImGui ${IMGUI_SOURCES})

#link all libraries to executable
target_link_libraries(${PROJECT_NAME} glfw GL Glad ImGui X11 pthread Xrandr
                        Xi ${CMAKE_DL_LIBS} stdc++fs)