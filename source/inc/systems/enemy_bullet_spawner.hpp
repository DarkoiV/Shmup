#pragma once
#include "Gng2D/types/scene.hpp"

struct EnemyBulletSpawner
{
    EnemyBulletSpawner(Gng2D::Scene& s)
        : scene(s) {}

    void operator()();

private:
    Gng2D::Scene& scene;
};

