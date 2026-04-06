# @file CMakeLists.txt
# @brief Top-level project definition for Lib Power Converter.

cmake_minimum_required(VERSION 3.21)

project(
    LibPowerConverter
    VERSION 0.1.0
    DESCRIPTION "Lib Power Converter common domain logic for baremetal power converter firmware"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LPC_STRICT_WARNINGS "Enable strict compiler warnings." ON)
option(LPC_ENABLE_LTO "Enable interprocedural optimization (LTO) when supported." OFF)
option(LPC_ENABLE_TESTS "Build host-side unit tests." ${PROJECT_IS_TOP_LEVEL})
option(LPC_ENFORCE_SINGLE_RETURN "Disallow multiple return statements in implementation files." ON)

add_library(lib_power_converter STATIC
    src/slew_rate_limiter.cpp
    src/pid_controller.cpp
)
add_library(lpc::core ALIAS lib_power_converter)

target_include_directories(lib_power_converter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(lib_power_converter PUBLIC cxx_std_11)

include(cmake/CompilerOptions.cmake)
lpc_apply_compiler_options(lib_power_converter)

if(LPC_ENFORCE_SINGLE_RETURN)
    add_custom_target(lpc_single_return_check
        COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_single_return.sh
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        COMMENT "Running single-return style rule"
        VERBATIM
    )
    add_dependencies(lib_power_converter lpc_single_return_check)
endif()

include(GNUInstallDirs)
install(TARGETS lib_power_converter
    EXPORT lpc-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT lpc-targets
    NAMESPACE lpc::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lpc
)

if(LPC_ENABLE_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        if(CMAKE_CROSSCOMPILING)
            message(STATUS "Skipping tests because CMAKE_CROSSCOMPILING is enabled.")
        else()
            add_subdirectory(tests)
        endif()
    endif()
endif()
