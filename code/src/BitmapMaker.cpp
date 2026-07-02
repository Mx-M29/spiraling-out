// BitmapMaker.cpp by Mx. M
// Created 5/25/2026
// BitmapMaker struct implementation
//
// Last modified 5/29/2026

#include "../include/BitmapMaker.hpp"

// Save a given simulation result to a bitmap file
std::string BitmapMaker::saveToFile(std::string filename, Spiral* spiral) {
    if (filename.length() < 4 || filename.compare(filename.length() - 4, 4, ".bmp") != 0) 
        filename = "output.bmp";

    auto &cells = *(spiral->getCells());
    int height = cells.size();
    int width = cells[0].size();
    int pad = 0;
    if ((width * 3) % 4 != 0) pad = 4 - ((width * 3) % 4);
    int fileSize = 54 + (((3 * width) + pad) * height);

    bmpHeader[2] = static_cast<unsigned char>(fileSize);
    bmpHeader[3] = static_cast<unsigned char>(fileSize >> 8);
    bmpHeader[4] = static_cast<unsigned char>(fileSize >> 16);
    bmpHeader[5] = static_cast<unsigned char>(fileSize >> 24);
    
    bmpInfoHeader[4]  = static_cast<unsigned char>(width);
    bmpInfoHeader[5]  = static_cast<unsigned char>(width >> 8);
    bmpInfoHeader[6]  = static_cast<unsigned char>(width >> 16);
    bmpInfoHeader[7]  = static_cast<unsigned char>(width >> 24);
    bmpInfoHeader[8]  = static_cast<unsigned char>(height);
    bmpInfoHeader[9]  = static_cast<unsigned char>(height >> 8);
    bmpInfoHeader[10] = static_cast<unsigned char>(height >> 16);
    bmpInfoHeader[11] = static_cast<unsigned char>(height >> 24);

    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(bmpHeader), 14);
    file.write(reinterpret_cast<const char*>(bmpInfoHeader), 40);

    for (int i = height-1; i >= 0; --i) {
        unsigned char pixelRow[(width * 3) + pad];
        int ctr = 0;

        for (int j=0; j < width; ++j) {
            Color color = cells[i][j].getColor();
            pixelRow[ctr++] = static_cast<unsigned char>(color.b);
            pixelRow[ctr++] = static_cast<unsigned char>(color.g);
            pixelRow[ctr++] = static_cast<unsigned char>(color.r);
        }
        for (int p=0; p < pad; ++p) pixelRow[ctr++] = static_cast<unsigned char>(0);

        file.write(reinterpret_cast<const char*>(pixelRow), (width * 3) + pad);
    }

    file.close();
    return filename;
}