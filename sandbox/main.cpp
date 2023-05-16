#include "Gng2D/core/application.hpp"

struct Sandbox : public Gng2D::Application
{
    void onCreate() override    {};
    void onQuit() override      {};
};

int main()
{
    Sandbox().run();
}
