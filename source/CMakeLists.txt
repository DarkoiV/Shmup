target_include_directories(shmup PUBLIC
    inc/)
target_sources(shmup PRIVATE
    src/systems/collision_system.cpp
    src/systems/enemy_bullet_spawner.cpp
    src/systems/entity_cleaner.cpp
    src/systems/entity_factory.cpp
    src/systems/player_controlls.cpp
    src/animations.cpp
    src/flight_scene.cpp
    src/game_over_scene.cpp
    src/levels.cpp
    src/main.cpp
    src/shmup.cpp)
