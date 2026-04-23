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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MayaCommon)

set(MAYA_OUTPUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/out/maya${MAYA_VERSION}")

add_subdirectory(plugins/hello_world_mll)
