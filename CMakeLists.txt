cmake_minimum_required(VERSION 3.22) 
project(Shmup)

# Create compile comands
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(lib/Gng2D)

add_executable(shmup)
target_link_libraries(shmup
    Gng2D)
set_target_properties(shmup PROPERTIES
    CXX_STANDARD                20
    RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}")

add_subdirectory(source)

