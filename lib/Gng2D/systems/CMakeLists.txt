# LIB
target_include_directories(Gng2D PUBLIC 
    inc/)
target_sources(Gng2D PRIVATE)

# Testing
target_sources(Gng2D_TESTS PRIVATE
    tst/collision_system_tests.cpp)
