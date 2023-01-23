#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"

Gng2D::Application::Application()
{
    LOG::OK("Created Gng2D application");
}

void Gng2D::Application::run()
{
    onCreate();
}

