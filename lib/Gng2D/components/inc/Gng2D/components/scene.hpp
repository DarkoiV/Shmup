#pragma once

namespace Gng2D
{

struct Scene
{
    virtual ~Scene() = default;

    virtual void onEnter()  = 0;
    virtual void onExit()   = 0;
    virtual void update()   = 0;
    virtual void render()   = 0;
};

}

