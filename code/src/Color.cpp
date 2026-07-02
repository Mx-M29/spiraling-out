// Color.cpp by Mx. M
// Created 5/24/2026
// Color struct implementation
//
// Last modified 5/24/2026

#include "../include/Color.hpp"

// Yeah it's just an ANSI code to change the console's background color
std::string Color::toConsole() {
    std::stringstream ss;
    ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
    return ss.str();
}