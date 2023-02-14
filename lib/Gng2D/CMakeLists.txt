cmake_minimum_required(VERSION 3.22) 
project(Gng2D)
include(FetchContent)
include(GoogleTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

add_library(Gng2D)

# Libraries
FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        fef921132cae7588213d0f9bcd2fb9c8ffd8b7fc # 3.11.1
)
FetchContent_MakeAvailable(Entt)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(Gng2D
    "${SDL2_LIBRARIES}"
    "${SDL2_IMAGE_LIBRARIES}"
    EnTT::EnTT)

# Testing
enable_testing()
add_executable(Gng2D_TESTS EXCLUDE_FROM_ALL)
target_link_libraries(Gng2D_TESTS
    Gng2D
    GTest::gtest_main
    GTest::gmock_main)
gtest_discover_tests(Gng2D_TESTS)
add_custom_target(Gng2D_run_test
    COMMAND Gng2D_TESTS)

add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(systems)
add_subdirectory(types)
