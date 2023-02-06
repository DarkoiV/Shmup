#pragma once
#include <memory>
#include <string>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include "Gng2D/core/log.hpp"

namespace Gng2D
{
struct Scene;

struct SceneRegistry
{
    using ScenePtr              = std::unique_ptr<Scene>;

    [[nodiscard]] Scene&    getCurrentScene() const;
    void                    switchScene();

    template<typename S, typename... Args>
        requires(std::is_base_of<Scene, S>::value)
    void setNextScene(Args&&... args)
    {
        nextScene = std::make_unique<S>(std::forward<Args>(args)...);
    }

private:
    inline static ScenePtr              currentScene;
    inline static ScenePtr              nextScene;
};
}

