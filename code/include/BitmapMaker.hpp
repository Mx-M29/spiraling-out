// BitmapMaker.hpp by Mx. M
// Created 5/25/2026
// BitmapMaker struct declaration
//
// Last modified 5/28/2026

#ifndef BITMAPMAKER_H
#define BITMAPMAKER_H

#include <fstream>
#include "Spiral.hpp"

/* BITMAP MAKER */
// Specialized class for creating bitmap files
struct BitmapMaker {
    // Bitmap header bytes
    unsigned char bmpHeader[14] = {66,77, 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpInfoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0, 0,0,0,0, 
                                       0,0,0,0, 196,14,0,0, 196,14,0,0, 0,0,0,0, 0,0,0,0};

    std::string saveToFile(std::string filename, Spiral* spiral);
};

#endif