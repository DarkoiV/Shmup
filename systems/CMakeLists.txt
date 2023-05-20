target_include_directories(Gng2D PUBLIC 
    inc/)
target_sources(Gng2D PRIVATE
    src/entity_renderer.cpp
    src/gui_system.cpp
    src/movement_system.cpp)

# Testing
target_sources(Gng2D_TESTS PRIVATE
    tst/overlap_system_tests.cpp)

