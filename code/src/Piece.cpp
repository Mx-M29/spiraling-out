// Piece.cpp by Mx. M
// Created 5/24/2026
// Implementation of Piece superclass and concrete subclasses
//
// Last modified 5/29/2026

#include "../include/Piece.hpp"

Piece::Piece(Color color, int enemies) : color(color), enemies(enemies) {
    this->attacked.resize(0);
}

Color Piece::getColor() { return color; }

int Piece::getEnemies() { return enemies; }

// Returns vector of global coordinates of cells targeted by the piece
std::vector<XY> Piece::attackedCells(XY xy, int ring, int rect) {
    auto xyAttacked = attacked;

    // Calculate global coordinates of targeted cells
    for (auto &atk : xyAttacked) {
        atk.x += xy.x; atk.y += xy.y;
    }

    // Dismiss coordinates that fall outside the board's dimensions
    for (int i = xyAttacked.size()-1; i >= 0; --i) {
        if (xyAttacked[i].x < 0 || xyAttacked[i].x > (2 * ring + rect) ||
            xyAttacked[i].y < 0 || xyAttacked[i].y > (2 * ring)) {
            xyAttacked.erase(xyAttacked.begin() + i);
        }
    }

    return xyAttacked;
}

// For this and all other pieces except Custom, the "attacked" vector is
// calculated based on the piece type's movement pattern and constructor params
Knight::Knight(Color color, int enemies, XY mv) : Piece(color, enemies) {
    attacked = std::vector<XY>{{- mv.x, - mv.y}, {- mv.x, + mv.y},
                               {- mv.y, - mv.x}, {- mv.y, + mv.x},
                               {+ mv.y, - mv.x}, {+ mv.y, + mv.x},
                               {+ mv.x, - mv.y}, {+ mv.x, + mv.y}};
}

Bishop::Bishop(Color color, int enemies, int rank) : Piece(color, enemies) {
    if (rank <= 0) { rank = 1; }
    attacked.reserve(4 * rank);

    for (int i=1; i <= rank; ++i) {
        std::vector<XY> rankAtk = {{+ i, + i},
                                   {+ i, - i},
                                   {- i, + i},
                                   {- i, - i}};
        attacked.insert(attacked.end(), rankAtk.begin(), rankAtk.end());
    }
}

Rook::Rook(Color color, int enemies, int rank) : Piece(color, enemies) {
    if (rank <= 0) { rank = 1; }
    attacked.reserve(4 * rank);

    for (int i=1; i <= rank; ++i) {
        std::vector<XY> rankAtk = {{+ i, 0},
                                   {- i, 0},
                                   {0, + i},
                                   {0, - i}};
        attacked.insert(attacked.end(), rankAtk.begin(), rankAtk.end());
    }
}

Queen::Queen(Color color, int enemies, int rank) : Piece(color, enemies) {
    if (rank <= 0) { rank = 1; }
    attacked.reserve(8 * rank);

    for (int i=1; i <= rank; ++i) {
        std::vector<XY> rankAtk = {{+ i, + i}, {+ i, 0},
                                   {+ i, - i}, {0, - i},
                                   {- i, - i}, {- i, 0},
                                   {- i, + i}, {0, + i}};
        attacked.insert(attacked.end(), rankAtk.begin(), rankAtk.end());
    }
}

King::King(Color color, int enemies, int rank) : Piece(color, enemies) {
    if (rank <= 0) { rank = 1; }
    attacked.reserve(8 * rank);

    for (int i=-rank; i <= rank; ++i) {
        attacked.push_back(XY{i, + rank});
        attacked.push_back(XY{i, - rank});
    }
    for (int i=-rank+1; i < rank; ++i) {
        attacked.push_back(XY{+ rank, i});
        attacked.push_back(XY{- rank, i});
    }
}

Taxi::Taxi(Color color, int enemies, int rank) : Piece(color, enemies) {
    if (rank <= 0) { rank = 1; }
    attacked.reserve(4 * rank);
    
    attacked = std::vector<XY>{{+ rank, 0},
                               {- rank, 0},
                               {0, + rank},
                               {0, - rank}};
    for (int i=1; i < rank; ++i) {
        std::vector<XY> rankAtk = {{i - rank, + i},
                                   {rank - i, + i},
                                   {i - rank, - i},
                                   {rank - i, - i}};
        attacked.insert(attacked.end(), rankAtk.begin(), rankAtk.end());
    }
}

// Custom just copies a pre-made "attacked" vector
Custom::Custom(Color color, int enemies, std::vector<XY> attacked) : Piece(color, enemies) {
    this->attacked = attacked;
}