#pragma once
#include <entt/entt.hpp>
#include <optional>
#include <string>
#include "Gng2D/components/selection_list.hpp"
#include "Gng2D/components/position.hpp"
#include "Gng2D/components/layer.hpp"
#include "Gng2D/types/font.hpp"
#include "Gng2D/types/menu_handle.hpp"

namespace Gng2D
{
struct EntityCompositor;
struct MenuBuilder
{
    MenuBuilder(entt::registry&);

    MenuBuilder&    withOnHighlightFunc(SelectionList::SelectionModFunc);
    MenuBuilder&    withOnStopHighlightFunc(SelectionList::SelectionModFunc);
    MenuBuilder&    withElement(const std::string&, SelectionList::SelectCallback);
    MenuBuilder&    withPosition(Position);
    MenuBuilder&    withVerticalSpace(unsigned);
    MenuBuilder&    withLayer(uint8_t);
    MenuBuilder&    withFont(const std::string& font);
    MenuBuilder&    withBox(const std::string& sprite, unsigned margin = 0);
    MenuHandle      build();

private:
    entt::registry& reg;
    using ElementToCreate = std::pair<std::string, SelectionList::SelectCallback>;
    std::vector<ElementToCreate> elementsToCreate;
  
    std::optional<Font>                 font;
    std::string                         boxTiles;
    unsigned                            boxMargin           = 0;
    unsigned                            verticalSpace       = 2;
    unsigned                            longestTextChars    = 0;
    std::optional<Position>             pos;
    uint8_t                             layer               = 100;

    SelectionList::SelectionModFunc                 onHighlightFunc;
    SelectionList::SelectionModFunc                 onStopHighlightFunc;

    void createSelectionList(EntityCompositor&, float elementVericalPos);
};
}

