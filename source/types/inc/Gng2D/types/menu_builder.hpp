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
    entt::entity    build();

    static void     setDefaultFont(const std::string& font);
    static void     setDefaultBox(const std::string& sprite, unsigned margin = 0);
    static void     setDefaultOnHighlightFunc(SelectionList::SelectionModFunc);
    static void     setDefaultOnStopHighlightFunc(SelectionList::SelectionModFunc);

private:
    entt::registry& reg;
    using ElementToCreate = std::pair<std::string, SelectionList::SelectCallback>;
    std::vector<ElementToCreate> elementsToCreate;
  
    inline static std::optional<Font>   defaultFont;
    std::optional<Font>                 font;
    inline static std::string           defaultBoxSpirteName;
    std::string                         boxSpriteName;
    inline static unsigned              defaultBoxMargin    = 0;
    unsigned                            boxMargin           = defaultBoxMargin;
    unsigned                            verticalSpace       = 4;
    unsigned                            longestTextChars    = 0;
    std::optional<Position>             pos;
    uint8_t                             layer               = 100;

    inline static SelectionList::SelectionModFunc   defaultOnHighlightFunc;
    SelectionList::SelectionModFunc                 onHighlightFunc;
    inline static SelectionList::SelectionModFunc   defaultOnStopHighlightFunc;
    SelectionList::SelectionModFunc                 onStopHighlightFunc;

    void createSelectionList(EntityCompositor&, float elementVericalPos);
};
}

