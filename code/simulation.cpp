// simulation.cpp by Mx. M
// Created 6/15/2026
// Main program function that runs a custom spiral chess simulation and creates an image from the result
//
// Last modified 6/15/2026

#include <filesystem>
#include "include/BitmapMaker.hpp"

#define LINK1 "\033]8;;"
#define LINK2 "\033\\"

int main() {
    /* PARAMETERS */
    // Ring = Spiral loops
    int ring = 500;
    // Rect = Rectangularity
    int rect = 0;

    /* PIECES */
    std::vector<Piece*> pieces;
    // Push in turn order
    // Knight, black, attacked by piece #2, movement = (2, 1)
    pieces.push_back(new Knight(Color{0, 0, 0}, 0b10, XY{2, 1}));
    // Knight, red, attacked by piece #1, movement = (2, 1)
    pieces.push_back(new Knight(Color{255, 0, 0}, 0b01, XY{2, 1}));

    /* RUN SIMULATION */
    Spiral game(ring, rect, std::move(pieces));
    game.playGame();

    /* MAKE BITMAP */
    BitmapMaker bitmap;
    std::string out = bitmap.saveToFile("output.bmp", &game);
    // Print hyperlink on the console
    std::cout << LINK1 << std::filesystem::current_path().string() << "\\" << out;
    std::cout << LINK2 << "Open generated map" << LINK1 << LINK2 << std::endl;
}