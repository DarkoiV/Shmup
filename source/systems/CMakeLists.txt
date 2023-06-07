target_include_directories(Gng2D PUBLIC 
    inc/)
target_sources(Gng2D PRIVATE
    src/animation_system.cpp
    src/entity_renderer.cpp
    src/gui_factory.cpp
    src/gui_system.cpp
    src/position_system.cpp)

# Testing
target_sources(Gng2D_TESTS PRIVATE
    tst/overlap_system_tests.cpp)

