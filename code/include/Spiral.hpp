// Spiral.hpp by Mx. M
// Created 5/24/2026
// Spiral class and SpiralIterator helper class declaration
//
// Last modified 5/26/2026

#ifndef SPIRAL_H
#define SPIRAL_H

#include <iostream>
#include "Cell.hpp"

#define CLR "\033[0m"

/* SPIRAL ITERATOR */
// Helper iterator class used to traverse a given spiral board
class SpiralIterator {
private:
    // Current cell
    XY xy; 
    // Current direction of travel
    XY dir;
    // Amount of cells traversed in the current direction
    int travel; 
    // Amount of cells to traverse before changing direction
    int toTravel; 
    // Board rectangularity
    int rect;

public:
    SpiralIterator(int ring = 0, int rect = 0);
    ~SpiralIterator() {}

    void changeDir();
    XY getNext();
};

/* SPIRAL */
// Main class in charge of running the simulation
class Spiral {
private:
    // Spiral board parameters
    int ring, rect;
    // Matrix of cells representing the entire board
    std::vector<std::vector<Cell>> cells;
    // Vector of spiral iterators for each piece
    std::vector<SpiralIterator> iterators;
    // Vector of pieces in play (or "players")
    std::vector<Piece*> pieces;

public:
    Spiral(int ring, int rect, std::vector<Piece*> pieces);
    ~Spiral();

    std::vector<std::vector<Cell>>* getCells();
    bool insideRange(XY xy);
    void playGame();
    void printGame();
};

#endif