set(TARGET_NAME hello_world_mll)

add_library(${TARGET_NAME} MODULE
    src/plugin_main.cpp
    src/hello_command.cpp
    include/hello_command.h
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_maya_mll(${TARGET_NAME})
