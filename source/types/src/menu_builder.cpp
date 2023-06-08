#include "Gng2D/types/menu_builder.hpp"
#include "Gng2D/types/entity_compositor.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/components/box.hpp"
#include "Gng2D/core/log.hpp"
#include "Gng2D/core/asset_registry.hpp"

using Gng2D::MenuBuilder;

MenuBuilder::MenuBuilder(entt::registry& reg)
    : reg(reg)
{
    if (defaultFont)                        font                = *defaultFont;
    if (not defaultBoxSpirteName.empty())   boxSpriteName       = defaultBoxSpirteName;
    if (defaultOnHighlightFunc)             onHighlightFunc     = defaultOnHighlightFunc;
    if (defaultOnStopHighlightFunc)         onStopHighlightFunc = defaultOnStopHighlightFunc;
}

MenuBuilder& MenuBuilder::withOnHighlightFunc(SelectionList::SelectionModFunc func)
{
    onHighlightFunc = func;
    return *this;
}

MenuBuilder& MenuBuilder::withOnStopHighlightFunc(SelectionList::SelectionModFunc func)
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
    boxSpriteName = sprite;
    boxMargin = margin;
    return *this;
}

entt::entity MenuBuilder::build()
{
    LOG::INFO("Building menu");
    if (not onHighlightFunc)
    {
        LOG::ERROR("Menu requires on highlight function");
        return entt::null;
    }
    if (not onStopHighlightFunc) 
    {
        LOG::ERROR("Menu requires on stop highlight function");
        return entt::null;
    }
    if (not pos)
    {
        LOG::ERROR("Menu requires positon");
        return entt::null;
    }
    if (not font)
    {
        LOG::ERROR("Menu requires font");
        return entt::null;
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

    if (not boxSpriteName.empty())
    {
        LOG::INFO("Menu with box:", boxSpriteName);
        baseEntityCompositor
            .with<Gng2D::Box>(boxSpriteName, width, height, boxMargin);
    }

    LOG::INFO("Menu built");
    return baseEntityCompositor.get();
}

void MenuBuilder::setDefaultFont(const std::string& font)
{
    defaultFont = AssetRegistry().getFont(font);
}

void MenuBuilder::setDefaultBox(const std::string& sprite, unsigned margin)
{
    defaultBoxSpirteName = sprite;
    defaultBoxMargin     = margin;
}

void MenuBuilder::setDefaultOnHighlightFunc(SelectionList::SelectionModFunc func)
{
    defaultOnHighlightFunc = func;
}

void MenuBuilder::setDefaultOnStopHighlightFunc(SelectionList::SelectionModFunc func)
{
    defaultOnStopHighlightFunc = func;
}

void MenuBuilder::createSelectionList(EntityCompositor& baseEntityCompositor, float elementVerticalPos)
{
    auto& selectionList = reg.get<SelectionList>(baseEntityCompositor.get());
    selectionList.onHighlight           = onHighlightFunc;
    selectionList.onStopHiglight        = onStopHighlightFunc;
    selectionList.highlightedSelection  = 0;

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

        selectionList.elements.emplace_back(selectionCompositor.get(), el.second);

        elementVerticalPos += (font->height() + verticalSpace);
    }

    baseEntityCompositor.modify<SelectionList>([&](auto& slist)
    {
        if (slist.elements.size() == 0) return;

        auto entity = slist.elements[0].first;
        reg.patch<Text>(entity, slist.onHighlight);
    });
}

