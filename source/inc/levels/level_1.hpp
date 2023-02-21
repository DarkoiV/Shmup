#include "Gng2D/systems/scene_control.hpp"

struct Level1 : Gng2D::SceneControl
{
    Level1(Gng2D::Scene& s)
        : Gng2D::SceneControl(s, coroutine()){};

    static Coroutine coroutine()
    {
        Gng2D::LOG::INFO("Hewwo! xD");
        while (true)
        {
            co_yield WaitTicks{60};
            Gng2D::LOG::INFO("60 ticks passed!");
        }
    }
};

