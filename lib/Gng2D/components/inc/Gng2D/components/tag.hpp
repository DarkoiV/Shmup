#pragma once
#include "Gng2D/types/game_object.hpp"

namespace Gng2D
{
template<typename Obj>
    requires(std::is_base_of<GameObject, Obj>::value)
struct Tag
{
};
}
