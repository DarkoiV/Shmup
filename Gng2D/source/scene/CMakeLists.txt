target_include_directories(Gng2D PUBLIC 
    inc/)
target_sources(Gng2D PRIVATE
    src/animation_system.cpp
    src/entity_renderer.cpp
    src/gui_system.cpp
    src/mouse_system.cpp
    src/position_system.cpp
    src/scene.cpp)

