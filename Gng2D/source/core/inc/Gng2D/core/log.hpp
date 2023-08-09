#pragma once

#include <string_view>
#include <iostream>

namespace Gng2D::LOG 
{
    namespace I // Internal
    {
        // Target stream
        inline auto& out = std::cout;

        constexpr std::string_view OK_TXT    = " [ OK    ] ";
        constexpr std::string_view INFO_TXT  = " [ INFO  ] ";
        constexpr std::string_view WARN_TXT  = " [ WARN  ] ";
        constexpr std::string_view ERROR_TXT = " [ ERROR ] ";
        constexpr std::string_view FATAL_TXT = " [ FATAL ] ";
    }

    template<typename... T>
    static void OK(T... msg) 
    {
        I::out << I::OK_TXT;
        ((I::out << " " << msg ), ... );
        I::out << "\n";
    }

    template<typename... T>
    static void INFO(T... msg) 
    {
        I::out << I::INFO_TXT;
        ((I::out << " " << msg ), ... );
        I::out << "\n";
    }

    template<typename... T>
    static void WARN(T... msg) 
    {
        I::out << I::WARN_TXT;
        ((I::out << " " << msg ), ... );
        I::out << "\n";
    }

    template<typename... T>
    static void ERROR(T... msg) 
    {
        I::out << I::ERROR_TXT;
        ((I::out << " " << msg ), ... );
        I::out << "\n";
    }

    template<typename... T>
    static void FATAL(T... msg) 
    {
        I::out << I::FATAL_TXT;
        ((I::out << " " << msg ), ... );
        I::out << "\n";
        std::exit(-1);
    }
}

