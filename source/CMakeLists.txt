target_include_directories(shmup PUBLIC
    inc/)
target_sources(shmup PRIVATE
    src/systems/bullet_bullet_collision.cpp
    src/systems/player_bullet_collision.cpp
    src/systems/player_weapons.cpp
    src/flight_scene.cpp
    src/main.cpp
    src/shmup.cpp)
