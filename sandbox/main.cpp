#include "Gng2D/core/application.hpp"
#include "Gng2D/components/text.hpp"
#include "Gng2D/types/scene.hpp"

struct TestScene : Gng2D::Scene
{
    void onEnter()                  override {}
    void onExit()                   override {}
    bool isCompleted()              override {return false;}
    void update()                   override {}
    void render(SDL_Renderer* r)    override
    {
        int w, h;
        SDL_QueryTexture(text.getSprite(), NULL, NULL, &w, &h);
        SDL_Rect dst{20, 20, w, h};
        SDL_RenderCopy(r, text.getSprite(), NULL, &dst); 

        static int x;
        x++;
        if(x == 60)
        {
            x = 0;
            text.changeString("NEW TEXT DISPLAY");
        }
    };

    Gng2D::Text text{"charmap-oldschool_white", "HELLO"};
};

struct Sandbox : public Gng2D::Application
{
    void onCreate() override
    {
        assetRegistry.loadBMFont("charmap-oldschool_white", 7, 9);
        sceneRegistry.setNextScene<TestScene>();
    }

    void onQuit() override      
    {
        stopRunning();
    };
};

int main()
{
    Sandbox().run();
}
