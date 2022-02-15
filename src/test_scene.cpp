#include "test_scene.hpp"

bool TestScene::eventHandler(SDL_Event &event)
{
    return false;
}

void TestScene::update()
{
}

bool TestScene::completed()
{
    return false;
}

auto TestScene::factory(EventManager& em) -> Scene*
{
    return new TestScene(em);
}
