cmake_minimum_required(VERSION 3.22) 
project(Sandbox)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
add_compile_options(-Wall -Wextra -Wpedantic)

FetchContent_Declare(
    Gng2D
    GIT_REPOSITORY  https://github.com/DarkoiV/Gng2D.git
    GIT_TAG         main
)
FetchContent_MakeAvailable(Gng2D)

add_executable(sandbox)
target_link_libraries(sandbox
    Gng2D)
set_target_properties(sandbox PROPERTIES
    CXX_STANDARD                20
    RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}")

target_sources(sandbox PRIVATE
    main.cpp)
