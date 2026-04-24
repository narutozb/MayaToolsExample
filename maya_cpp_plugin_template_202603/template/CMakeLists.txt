cmake_minimum_required(VERSION 3.24)

project(MayaCppPluginTemplate LANGUAGES CXX)

# TODO(project-manager): 固定长期项目使用的 C++ 标准，并在升级前评估对旧 Maya 版本的影响。
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO(project-manager): 如需统一构建版本，请在 CI 或 Preset 中集中管理 MAYA_VERSION。
if(NOT DEFINED MAYA_VERSION)
    set(MAYA_VERSION 2026)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(MayaVersionSwitch)
include(MayaCommon)

resolve_maya_location(${MAYA_VERSION})

if(NOT EXISTS "${MAYA_INCLUDE_DIR}/maya/MPxCommand.h")
    message(FATAL_ERROR "Maya header not found: ${MAYA_INCLUDE_DIR}/maya/MPxCommand.h")
endif()

if(NOT EXISTS "${MAYA_LIBRARY_DIR}")
    message(FATAL_ERROR "Maya library directory not found: ${MAYA_LIBRARY_DIR}")
endif()

message(STATUS "MAYA_VERSION     = ${MAYA_VERSION}")
message(STATUS "MAYA_LOCATION    = ${MAYA_LOCATION}")
message(STATUS "MAYA_INCLUDE_DIR = ${MAYA_INCLUDE_DIR}")
message(STATUS "MAYA_LIBRARY_DIR = ${MAYA_LIBRARY_DIR}")

# TODO(project-manager): 如需按团队发布规范输出 zip/package，可在此处追加统一的打包目标。
set(MAYA_OUTPUT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/out/maya${MAYA_VERSION}")
set(SHARED_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shared/include")

add_subdirectory(plugins/hello_world_mll)
add_subdirectory(plugins/scene_tools_mll)
add_subdirectory(plugins/utility_tools_mll)
