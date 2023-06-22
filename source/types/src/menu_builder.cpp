#include "Gng2D/types/menu_builder.hpp"
#include "Gng2D/components/box.hpp"
#include "Gng2D/components/mouse_controlls.hpp"
#include "Gng2D/components/relationship.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/core/asset_registry.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/scene/gui_system.hpp"
#include "Gng2D/types/entity_compositor.hpp"

using Gng2D::MenuBuilder;

MenuBuilder::MenuBuilder(entt::registry& reg)
    : reg(reg)
{
    font                = AssetRegistry().getDefaultFont();
    boxTiles            = AssetRegistry().getDefaultBoxTiles(); 
    onHighlightFunc     = AssetRegistry().getDefaultOnHighlightFunc();
    onStopHighlightFunc = AssetRegistry().getDefaultOnStopHighlightFunc();
}

MenuBuilder& MenuBuilder::withOnHighlightFunc(SelectionList::ModFunc func)
{
    onHighlightFunc = func;
    return *this;
}

MenuBuilder& MenuBuilder::withOnStopHighlightFunc(SelectionList::ModFunc func)
{
    onStopHighlightFunc = func;
    return *this;
}

MenuBuilder& MenuBuilder::withElement(const std::string& str, SelectionList::SelectCallback callback)
{
    longestTextChars = str.size() > longestTextChars 
                     ? str.size() 
                     : longestTextChars;
    elementsToCreate.emplace_back(str, callback);
    return *this;
}

MenuBuilder& MenuBuilder::withPosition(Position p)
{
    pos = p;
    return *this;
}

MenuBuilder& MenuBuilder::withVerticalSpace(unsigned vs)
{
    verticalSpace = vs;
    return *this;
}

MenuBuilder& MenuBuilder::withLayer(uint8_t main)
{
    layer = main;
    return *this;
}

MenuBuilder& MenuBuilder::withFont(const std::string& fontName)
{
    font = AssetRegistry().getFont(fontName);
    return *this;
}

MenuBuilder& MenuBuilder::withBox(const std::string& sprite, unsigned margin)
{
    boxTiles = AssetRegistry().getSprite(sprite);
    boxMargin = margin;
    return *this;
}

MenuBuilder& MenuBuilder::withMouseSupport()
{
    supportMouse = true;
    return *this;
}

Gng2D::MenuHandle MenuBuilder::build()
{
    LOG::INFO("Building menu");
    if (not onHighlightFunc)
    {
        LOG::ERROR("Menu requires on highlight function");
        return {reg, entt::null};
    }
    if (not onStopHighlightFunc) 
    {
        LOG::ERROR("Menu requires on stop highlight function");
        return {reg, entt::null};
    }
    if (not pos)
    {
        LOG::ERROR("Menu requires positon");
        return {reg, entt::null};
    }
    if (not font)
    {
        LOG::ERROR("Menu requires font");
        return {reg, entt::null};
    }
    if (elementsToCreate.size() == 0)
    {
        LOG::ERROR("Menu needs at least one element");
        return {reg, entt::null};
    }

    auto baseEntityCompositor = EntityCompositor(reg)
        .with<Gng2D::SelectionList>()
        .with<Gng2D::Position>(*pos)
        .with<Gng2D::Layer>(layer);

    unsigned vSpacesCount = elementsToCreate.size() > 1 
                          ? elementsToCreate.size() - 1 
                          : 0;
    unsigned width  = longestTextChars * font->width();
    unsigned height = vSpacesCount * verticalSpace 
                    + elementsToCreate.size() * font->height();
    LOG::INFO("Menu dimensions", width, "x", height);

    float firstElementPos = 0.0f 
                          - (static_cast<float>(height) / 2) 
                          + (static_cast<float>(font->height()) / 2);
    createSelectionList(baseEntityCompositor, firstElementPos);

    if (boxTiles)
    {
        baseEntityCompositor
            .with<Gng2D::Box>(boxTiles, width, height, boxMargin);
    }

    LOG::INFO("Menu built");
    return {reg, baseEntityCompositor.get()};
}

void MenuBuilder::createSelectionList(EntityCompositor& baseEntityCompositor, float elementVerticalPos)
{
    auto& selectionList = reg.get<SelectionList>(baseEntityCompositor.get());
    selectionList.onHighlight           = onHighlightFunc;
    selectionList.onStopHiglight        = onStopHighlightFunc;
    selectionList.highlightedSelection  = 0;

    auto mouseHoverEnter = [](entt::registry& reg, entt::entity entity)
    {
        auto selectionListEntity = reg.get<Gng2D::Parent>(entity).id;
        auto& sl = reg.get<SelectionList>(selectionListEntity);
        for (size_t i = 0; i < sl.elements.size(); i++)
        {
            if (sl.elements[i].entity == entity)
            {
                sl.highlightedSelection = i;
                reg.patch<Text>(sl.elements[i].entity, sl.onHighlight);
            }
            else 
            {
                reg.patch<Text>(sl.elements[i].entity, sl.onStopHiglight);
            }
        }
    };

    auto mouseClick = [](entt::registry& reg, entt::entity entity)
    {
        auto selectionListEntity = reg.get<Gng2D::Parent>(entity).id;
        auto& sl = reg.get<SelectionList>(selectionListEntity);
        for (auto& el : sl.elements) 
            if (el.entity == entity) return el.callback();
    };

    for (auto& el : elementsToCreate)
    {
        LOG::INFO("Adding to menu:", 
                  el.first, 
                  "with relative posistion: 0 x ", 
                  elementVerticalPos);
        auto selectionCompositor = EntityCompositor(reg)
            .with<Gng2D::Text>(*font, el.first)
            .withParent(baseEntityCompositor.get())
            .with<Gng2D::RelativePosition>(0.0f, elementVerticalPos);

        if (supportMouse)
        {
            selectionCompositor
                .with<Hoverable>(mouseHoverEnter, [](entt::registry&, entt::entity){})
                .with<UseSpriteHoverArea>()
                .with<Clickable>(mouseClick);
        }

        selectionList.elements.push_back({selectionCompositor.get(), el.second});

        elementVerticalPos += (font->height() + verticalSpace);
    }

    baseEntityCompositor.modify<SelectionList>([&](auto& slist)
    {
        auto element = slist.elements.begin();
        reg.patch<Text>(element->entity, slist.onHighlight);
        while(++element != slist.elements.end())
        {    
            reg.patch<Text>(element->entity, slist.onStopHiglight);
        }
    });
}

