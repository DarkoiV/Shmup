#pragma once
#include "Gng2D/types/scene.hpp"

struct EntityCleaner
{
    EntityCleaner(Gng2D::Scene&);

    void operator()();
private:
    Gng2D::Scene& scene;

    void outOfScreenCleaner();
};

