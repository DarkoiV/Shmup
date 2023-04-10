target_include_directories(shmup PUBLIC
    inc/)
target_sources(shmup PRIVATE
    src/components/enemy_animation.cpp
    src/systems/animations_system.cpp
    src/systems/bullet_bullet_collision.cpp
    src/systems/bullet_enemy_collision.cpp
    src/systems/entity_cleaner.cpp
    src/systems/enemy_bullet_spawner.cpp
    src/systems/flight_scene_gui.cpp
    src/systems/player_bullet_collision.cpp
    src/systems/player_controlls.cpp
    src/systems/player_enemy_collision.cpp
    src/flight_scene.cpp
    src/game_over_scene.cpp
    src/levels.cpp
    src/main.cpp
    src/shmup.cpp)
