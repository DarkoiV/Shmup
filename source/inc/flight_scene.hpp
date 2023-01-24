#pragma once
#include "Gng2D/components/scene.hpp"

struct FlightScene : public Gng2D::Scene
{
    void onEnter()      override;
    void onExit()       override;
    bool isCompleted()  override;
    void update()       override;
};
