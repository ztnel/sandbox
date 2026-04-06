# @file tests/CMakeLists.txt
# @brief Configures host-side GoogleTest and GoogleMock unit test targets.

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Keep Windows users from overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lpc_tests
    test_slew_rate_limiter.cpp
    test_pid_controller.cpp
)

target_link_libraries(lpc_tests
    PRIVATE
        lpc::core
        GTest::gtest_main
        GTest::gmock
)

target_compile_features(lpc_tests PRIVATE cxx_std_11)

include(GoogleTest)
gtest_discover_tests(lpc_tests)
