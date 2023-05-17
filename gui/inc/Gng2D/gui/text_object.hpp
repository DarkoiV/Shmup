#include "Gng2D/types/game_object.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/text_sprite.hpp"

namespace Gng2D
{
struct TextObject : GameObject
{
    using Gng2D::GameObject::GameObject;

    void onCreate(Gng2D::Position p, 
                  const std::string& font, 
                  const std::string& str, 
                  float scale = 1, 
                  uint8_t layer = 255)
    {
        addComponent<Layer>(layer);
        addComponent<TextSprite>(font, str, scale);
        addComponent<Gng2D::Position>(p);
    }
};
}

