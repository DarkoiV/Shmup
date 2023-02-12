target_include_directories(shmup PUBLIC
    inc/)
target_sources(shmup PRIVATE
    src/bullet_bullet_collision_system.cpp
    src/player_bullet_collision_system.cpp
    src/flight_scene.cpp
    src/main.cpp
    src/shmup.cpp)
