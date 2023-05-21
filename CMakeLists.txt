cmake_minimum_required(VERSION 3.22) 
project(Shmup)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
add_compile_options(-Wall -Wextra -Wpedantic)

#Gng2D DEV MODE
if(EXISTS "${CMAKE_SOURCE_DIR}/Gng2D-DEV")
    message("Using Gng2D-DEV")
    add_subdirectory(Gng2D-DEV)
else()
    FetchContent_Declare(
        Gng2D
        GIT_REPOSITORY  https://github.com/DarkoiV/Gng2D.git
        GIT_TAG         main
    )
    FetchContent_MakeAvailable(Gng2D)
endif()

add_executable(shmup)
target_link_libraries(shmup
    Gng2D)
set_target_properties(shmup PROPERTIES
    CXX_STANDARD                20
    RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}")

add_subdirectory(source)

