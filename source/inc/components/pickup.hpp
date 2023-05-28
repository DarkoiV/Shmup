#pragma once

struct Pickup 
{
    enum class Type 
    {
        drones
    } type;

    Pickup(Type t)
        : type(t) {}
};

