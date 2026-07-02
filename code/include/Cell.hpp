// Cell.hpp by Mx. M
// Created 5/24/2026
// Cell class declaration
//
// Last modified 6/5/2026

#ifndef CELL_H
#define CELL_H

#include "Piece.hpp"

/* CELL */
// Represents a square in a given spiral board
// Contains piece info and targeted status
class Cell {
private:
    // Pointer to piece occupying the cell
    Piece* piece;
    // Integer describing which pieces are currently targeting it
    int attackers;

public:
    Cell();
    ~Cell() {}

    bool isEmpty();
    bool isFriendly(int enemies);
    Color getColor();
    std::vector<XY> setPiece(Piece* p, XY xy, int ring, int rect);
    void setAttacker(int color);
};

#endif