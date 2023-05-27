#pragma once
#include <entt/entt.hpp>

struct EntityCleaner
{
    EntityCleaner(entt::registry&);

    void operator()();
private:
    entt::registry& reg;

    void outOfScreenCleaner();
    void destroyedCleaner();

    void spawnRedX(entt::entity);
};

