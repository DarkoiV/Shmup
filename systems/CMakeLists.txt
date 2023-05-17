target_include_directories(Gng2D PUBLIC 
    inc/)
target_sources(Gng2D PRIVATE
    src/movement_system.cpp
    src/entity_renderer.cpp)

# Testing
target_sources(Gng2D_TESTS PRIVATE
    tst/overlap_system_tests.cpp)

