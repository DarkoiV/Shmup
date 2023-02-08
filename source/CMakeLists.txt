target_include_directories(shmup PUBLIC
    inc/)
target_sources(shmup PRIVATE
    src/flight_scene.cpp
    src/main.cpp
    src/shmup.cpp)
