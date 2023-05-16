#pragma once
#include "Gng2D/types/scene.hpp"

namespace Gng2D
{
struct MovementSystem
{
    MovementSystem(Gng2D::Scene&);
    void operator()();

protected:
    void updatePosition();

    Gng2D::Scene& scene;
};
}
