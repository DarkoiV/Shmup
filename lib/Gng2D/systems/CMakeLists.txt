# LIB
target_include_directories(Gng2D PUBLIC 
    inc/)
target_sources(Gng2D PRIVATE
    src/movement_system.cpp
    src/scene_control.cpp)

# Testing
target_sources(Gng2D_TESTS PRIVATE
    tst/overlap_system_tests.cpp)
