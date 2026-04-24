set(TARGET_NAME utility_tools_mll)

# TODO(developer): 新增命令或节点时，请统一只改 TARGET_SOURCES 与 plugin_features.cpp。
set(TARGET_SOURCES
    src/plugin_main.cpp
    src/plugin_features.cpp
    src/build_info_command.cpp
    src/negate_value_node.cpp
    include/plugin_features.h
    include/build_info_command.h
    include/negate_value_node.h
)

add_library(${TARGET_NAME} MODULE ${TARGET_SOURCES})

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SHARED_INCLUDE_DIR}
)

apply_default_source_groups(${TARGET_NAME} ${TARGET_SOURCES})
configure_maya_mll(${TARGET_NAME})
