// Cell.cpp by Mx. M
// Created 5/24/2026
// Cell class implementation
//
// Last modified 6/5/2026

#include "../include/Cell.hpp"

Cell::Cell() {
    this->piece = nullptr;
    this->attackers = 0;
}

bool Cell::isEmpty() { return piece == nullptr; }

// Whether or not a piece can be placed in this cell
bool Cell::isFriendly(int enemies) {
    // If just one of the pieces targeting the cell threatens the piece
    // trying to place here, the cell is deemed unfriendly
    return !(attackers & enemies);
}

Color Cell::getColor() {
    // An empty cell returns white
    if (isEmpty()) return Color{255, 255, 255};
    else return piece->getColor();
}

// Place a piece in the cell and return the coordinates of affected cells
std::vector<XY> Cell::setPiece(Piece* p, XY xy, int ring, int rect) {
    piece = p;
    auto attacked = piece->attackedCells(xy, ring, rect);
    return attacked;
}

void Cell::setAttacker(int color) {
    // Don't update attackers if the cell is already occupied
    if (isEmpty()) {
        attackers |= 0x1 << color;
    }
}