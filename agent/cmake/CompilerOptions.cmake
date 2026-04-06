# @file CompilerOptions.cmake
# @brief Central compiler warning/optimization policy for project targets.

function(lpc_apply_compiler_options target_name)
    if(NOT TARGET ${target_name})
        message(FATAL_ERROR "Target '${target_name}' does not exist.")
    endif()

    if(LPC_STRICT_WARNINGS)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target_name} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wshadow
                -Wconversion
                -Wsign-conversion
            )
        elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_compile_options(${target_name} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Wshadow
                -Wconversion
                -Wsign-conversion
            )
        endif()
    endif()

    if(CMAKE_SYSTEM_NAME STREQUAL "Generic")
        target_compile_options(${target_name} PRIVATE
            -ffreestanding
            -fno-exceptions
            -fno-rtti
            -fdata-sections
            -ffunction-sections
        )
    endif()

    if(LPC_ENABLE_LTO)
        include(CheckIPOSupported)
        check_ipo_supported(RESULT has_ipo OUTPUT ipo_output)
        if(has_ipo)
            set_property(TARGET ${target_name} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
        else()
            message(WARNING "IPO/LTO requested but not supported: ${ipo_output}")
        endif()
    endif()
endfunction()
