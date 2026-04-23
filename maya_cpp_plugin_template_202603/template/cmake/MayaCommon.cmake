function(configure_maya_mll TARGET_NAME)
    target_include_directories(${TARGET_NAME}
        PRIVATE
            "${MAYA_INCLUDE_DIR}"
    )

    target_link_directories(${TARGET_NAME}
        PRIVATE
            "${MAYA_LIBRARY_DIR}"
    )

    target_link_libraries(${TARGET_NAME}
        PRIVATE
            Foundation
            OpenMaya
            OpenMayaAnim
            OpenMayaUI
        )

    target_compile_definitions(${TARGET_NAME}
        PRIVATE
            _BOOL
            REQUIRE_IOSTREAM
            NT_PLUGIN
            _CRT_SECURE_NO_WARNINGS
    )

    if(MSVC)
        target_compile_options(${TARGET_NAME}
            PRIVATE
                /W4
                /EHsc
        )
    endif()

    set_target_properties(${TARGET_NAME}
        PROPERTIES
            PREFIX ""
            SUFFIX ".mll"
            RUNTIME_OUTPUT_DIRECTORY "${MAYA_OUTPUT_ROOT}/$<CONFIG>"
            LIBRARY_OUTPUT_DIRECTORY "${MAYA_OUTPUT_ROOT}/$<CONFIG>"
    )
endfunction()

function(apply_default_source_groups TARGET_NAME)
    foreach(_file IN LISTS ARGN)
        get_filename_component(_absolute_path "${_file}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        file(RELATIVE_PATH _relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${_absolute_path}")
        get_filename_component(_relative_dir "${_relative_path}" DIRECTORY)

        if(_relative_dir STREQUAL "")
            set(_group_name "Root")
        else()
            string(REPLACE "/" "\\" _group_name "${_relative_dir}")
        endif()

        source_group("${_group_name}" FILES "${_absolute_path}")
    endforeach()
endfunction()
