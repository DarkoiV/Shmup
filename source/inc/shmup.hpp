#pragma once
#include "Gng2D/core/application.hpp"
#include "Gng2D/core/log.hpp"

struct Shmup : public Gng2D::Application
{
    void onCreate() override;
    void onQuit() override;
};
