# TODO(project-manager): 如需支持更多 Maya 版本，请在此文件中追加版本与环境变量的映射规则。
function(resolve_maya_location MAYA_VERSION_INPUT)
    set(_maya_location "")

    if(MAYA_VERSION_INPUT STREQUAL "2024")
        set(_maya_location "$ENV{MAYA_LOCATION_2024}")
    elseif(MAYA_VERSION_INPUT STREQUAL "2025")
        set(_maya_location "$ENV{MAYA_LOCATION_2025}")
    elseif(MAYA_VERSION_INPUT STREQUAL "2026")
        set(_maya_location "$ENV{MAYA_LOCATION_2026}")
    endif()

    # TODO(project-manager): 如果团队仅维护单一版本 Maya，可只保留 MAYA_LOCATION 并删除版本分支。
    if(_maya_location STREQUAL "")
        set(_maya_location "$ENV{MAYA_LOCATION}")
    endif()

    if(_maya_location STREQUAL "")
        message(FATAL_ERROR
            "Maya location is not set. Please set MAYA_LOCATION or MAYA_LOCATION_${MAYA_VERSION_INPUT}."
        )
    endif()

    set(MAYA_LOCATION "${_maya_location}" PARENT_SCOPE)
    set(MAYA_INCLUDE_DIR "${_maya_location}/include" PARENT_SCOPE)
    set(MAYA_LIBRARY_DIR "${_maya_location}/lib" PARENT_SCOPE)
endfunction()
