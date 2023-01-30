#pragma once
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "Gng2D/components/scene.hpp"
#include "Gng2D/core/log.hpp"

namespace Gng2D
{
struct SceneRegistry
{
    using ScenePtr              = std::unique_ptr<Scene>;
    using SceneFactory          = std::function<ScenePtr()>;
    using RegisteredFactories   = std::unordered_map<std::string, SceneFactory>;

    template<typename S>
    static void registerScene(const std::string& name)
    {
        LOG::INFO("Registering scene:", name);
        registered[name] = []() -> ScenePtr
        {
            return std::make_unique<S>();
        };
    }

    auto scene()            -> Scene&;
    void setNextScene(const std::string& name);
    void switchScene();

private:
    ScenePtr    currentScene;
    ScenePtr    nextScene;

    inline static RegisteredFactories registered;
};
}

#define GNG2D_REGISTER_SCENE(SCENE) Gng2D::SceneRegistry::registerScene<SCENE>(#SCENE)
