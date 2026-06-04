cmake_minimum_required(VERSION 2.8)
project(service_manager CXX)

# Force C++03 for prototype
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03 -Wall -Wextra")

add_library(service_manager STATIC src/service_manager.cpp)
target_include_directories(service_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(example_main examples/main.cpp)
target_link_libraries(example_main service_manager)

# Tests
enable_testing()
add_subdirectory(tests)
