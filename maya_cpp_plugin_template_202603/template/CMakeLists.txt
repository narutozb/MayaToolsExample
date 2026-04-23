cmake_minimum_required(VERSION 3.24)

project(MayaCppPluginTemplate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT DEFINED MAYA_VERSION)
    set(MAYA_VERSION 2026)
endif()

if(NOT DEFINED ENV{MAYA_LOCATION})
    message(FATAL_ERROR "Environment variable MAYA_LOCATION is not set.")
endif()

set(MAYA_LOCATION "$ENV{MAYA_LOCATION}")
set(MAYA_INCLUDE_DIR "${MAYA_LOCATION}/include")
set(MAYA_LIBRARY_DIR "${MAYA_LOCATION}/lib")

if(NOT EXISTS "${MAYA_INCLUDE_DIR}/maya/MPxCommand.h")
    message(FATAL_ERROR "Maya header not found: ${MAYA_INCLUDE_DIR}/maya/MPxCommand.h")
endif()

if(NOT EXISTS "${MAYA_LIBRARY_DIR}")
    message(FATAL_ERROR "Maya library directory not found: ${MAYA_LIBRARY_DIR}")
endif()

message(STATUS "MAYA_LOCATION    = ${MAYA_LOCATION}")
message(STATUS "MAYA_INCLUDE_DIR = ${MAYA_INCLUDE_DIR}")
message(STATUS "MAYA_LIBRARY_DIR = ${MAYA_LIBRARY_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MayaCommon)

set(MAYA_OUTPUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/out/maya${MAYA_VERSION}")

add_subdirectory(plugins/hello_world_mll)
