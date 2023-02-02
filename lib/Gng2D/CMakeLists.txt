cmake_minimum_required(VERSION 3.22) 
project(Gng2D)
include (FetchContent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}) 

add_library(Gng2D)

# Libraries
FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        fef921132cae7588213d0f9bcd2fb9c8ffd8b7fc # 3.11.1
)
FetchContent_MakeAvailable(Entt)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(Gng2D
    "${SDL2_LIBRARIES}"
    "${SDL2_IMAGE_LIBRARIES}"
    EnTT::EnTT)

add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(internal)
add_subdirectory(systems)
