#pragma once
#include <memory>
#include <vector>
#include "Gng2D/components/scene.hpp"
#include "Gng2D/components/game_object.hpp"

struct FlightScene : public Gng2D::Scene
{
    void onEnter()      override;
    void onExit()       override;
    bool isCompleted()  override;
    void update()       override;

private:
    using SceneObject = std::unique_ptr<Gng2D::GameObject>;
    std::vector<SceneObject> sceneObjects;
};
