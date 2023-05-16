cmake_minimum_required(VERSION 3.22) 
project(Shmup)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
add_compile_options(-Wall -Wextra -Wpedantic)

FetchContent_Declare(
    Gng2D
    GIT_REPOSITORY  https://github.com/DarkoiV/Gng2D.git
    GIT_TAG         e2092134ba7e95162a176fc697a476d1210d5158
)
FetchContent_MakeAvailable(Gng2D)

add_executable(shmup)
target_link_libraries(shmup
    Gng2D)
set_target_properties(shmup PROPERTIES
    CXX_STANDARD                20
    RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}")

add_subdirectory(source)

