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
