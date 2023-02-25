#pragma once
#include <vector>
#include "Gng2D/types/coroutine.hpp"

namespace Gng2D
{
struct Scene;
struct SceneController
{
    SceneController(Scene& s);

    template<typename Coro>
    void addSceneCoroutine(Coro c)
    {
        coroutines.emplace_back(c, scene);
    };

    void operator()();

private:
    Scene&                  scene;
    std::vector<Coroutine>  coroutines;
};
}

