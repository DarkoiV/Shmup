#pragma once
#include <entt/entt.hpp>
#include <optional>
#include <string>
#include "Gng2D/components/selection_list.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/types/font.hpp"

namespace Gng2D
{
struct MenuBuilder
{
    MenuBuilder(entt::registry&);

    MenuBuilder&    withOnHighlightFunc(SelectionList::OnHighlight);
    MenuBuilder&    withOnStopHighlightFunc(SelectionList::OnStopHighlight);
    MenuBuilder&    withElement(const std::string&, SelectionList::SelectCallback);
    MenuBuilder&    withPosition(Position);
    MenuBuilder&    withLayer(uint8_t);
    MenuBuilder&    withFont(const std::string& font);
    MenuBuilder&    withBox(const std::string& sprite, unsigned margin = 0);
    entt::entity    build();

private:
    entt::registry& reg;
    using ElementToCreate = std::pair<std::string, SelectionList::SelectCallback>;
    std::vector<ElementToCreate> elementsToCreate;
  
    std::optional<Font> font;
    std::string boxSpriteName;
    unsigned boxMargin;
    unsigned verticalSpace      = 4;
    unsigned longestTextChars   = 0;
    std::optional<Position> pos;
    uint8_t layer{100};

    SelectionList::OnHighlight      onHighlightFunc;
    SelectionList::OnStopHighlight  onStopHighlightFunc;
};
}

