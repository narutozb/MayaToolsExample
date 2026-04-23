set(TARGET_NAME scene_tools_mll)

add_library(${TARGET_NAME} MODULE
    src/plugin_main.cpp
    src/plugin_features.cpp
    src/maya_version_command.cpp
    src/list_selection_command.cpp
    src/clamp_value_node.cpp
    include/plugin_features.h
    include/maya_version_command.h
    include/list_selection_command.h
    include/clamp_value_node.h
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SHARED_INCLUDE_DIR}
)

configure_maya_mll(${TARGET_NAME})
