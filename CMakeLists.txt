cmake_minimum_required(VERSION 3.22) 
project(Shmup)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create compile comands
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")

add_subdirectory(lib/Gng2D)
add_executable(shmup
    source/shmup.cpp)
target_link_libraries(shmup
    Gng2D)
