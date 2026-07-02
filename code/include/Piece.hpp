// Piece.hpp by Mx. M
// Created 5/24/2026
// Declaration of Piece superclass and concrete subclasses
//
// Last modified 5/29/2026

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Color.hpp"

/* XY */
// Simple struct for coordinate representation
struct XY {
    int x, y;
};

/* PIECE */
// Superclass that defines piece behavior
class Piece {
protected:
    // Vector of relative coordinates of cells targeted by the piece
    std::vector<XY> attacked; 
    // Piece color
    Color color;
    // Integer describing this piece's relationship to other pieces
    int enemies;
    
    Piece(Color color, int enemies);

public:
    virtual ~Piece() = default;

    Color getColor();
    int getEnemies();
    std::vector<XY> attackedCells(XY xy, int ring, int rect);
};

/* KNIGHT */
class Knight : public Piece {
public:
    Knight(Color color = {0, 0, 0}, int enemies = 0, XY mv = {2, 1});
    ~Knight() {}
};

/* BISHOP */
// Rank = Range
class Bishop : public Piece {
public:
    Bishop(Color color = {0, 0, 0}, int enemies = 0, int rank = 2);
    ~Bishop() {}
};

/* ROOK */
class Rook : public Piece {
public:
    Rook(Color color = {0, 0, 0}, int enemies = 0, int rank = 2);
    ~Rook() {}
};

/* QUEEN */
class Queen : public Piece {
public:
    Queen(Color color = {0, 0, 0}, int enemies = 0, int rank = 2);
    ~Queen() {}
};

/* KING */
class King : public Piece {
public:
    King(Color color = {0, 0, 0}, int enemies = 0, int rank = 2);
    ~King() {}
};

/* TAXI */
class Taxi : public Piece {
public:
    Taxi(Color color = {0, 0, 0}, int enemies = 0, int rank = 2);
    ~Taxi() {}
};

/* CUSTOM */
class Custom : public Piece {
public:
    Custom(Color color = {0, 0, 0}, int enemies = 0, std::vector<XY> attacked = {{0, 0}});
    ~Custom() {}
};

#endif