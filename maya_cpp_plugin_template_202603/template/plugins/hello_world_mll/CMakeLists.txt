set(TARGET_NAME hello_world_mll)

add_library(${TARGET_NAME} MODULE
    src/plugin_main.cpp
    src/plugin_features.cpp
    src/hello_command.cpp
    src/echo_text_command.cpp
    src/add_value_node.cpp
    include/plugin_features.h
    include/hello_command.h
    include/echo_text_command.h
    include/add_value_node.h
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SHARED_INCLUDE_DIR}
)

configure_maya_mll(${TARGET_NAME})
