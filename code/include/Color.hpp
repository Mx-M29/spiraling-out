// Color.hpp by Mx. M
// Created 5/24/2026
// Color struct declaration
//
// Last modified 5/24/2026

#ifndef COLOR_H
#define COLOR_H

#include <sstream>

/* COLOR */
struct Color {
    unsigned int r, g, b;

    // The only reason why Color has its own header
    // Unused in the current code
    std::string toConsole();
};

#endif