#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"

struct Shmup : public Gng2D::Application
{
    void onCreate() override
    {
        Gng2D::LOG::INFO("Creating Shmup");
    }

    void onQuit() override
    {
        stopRunning();
    }
};

int main()
{
    Shmup().run();
}
