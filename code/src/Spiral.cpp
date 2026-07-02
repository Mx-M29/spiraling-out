// Spiral.cpp by Mx. M
// Created 5/24/2026
// Spiral class and SpiralIterator helper class implementation
//
// Last modified 6/5/2026

#include "../include/Spiral.hpp"

SpiralIterator::SpiralIterator(int ring, int rect) {
    // Initialize the iterator one cell before cell #0
    this->xy = {ring - 1, ring};
    this->rect = rect;
    // Initial direction is right
    this->dir = {1, 0};
    this->toTravel = 1;
    this->travel = -1;
}

void SpiralIterator::changeDir() {
    // Each direction change is counterclockwise
    if (dir.x == 0) {
        toTravel++;
        dir.x = dir.y; dir.y = 0;
    } else {
        dir.y = -dir.x; dir.x = 0;
    }
}

XY SpiralIterator::getNext() {
    xy.x += dir.x; xy.y += dir.y;
    travel++;

    // Account for board rectangularity
    int r = (dir.x == 0) ? 0 : rect;
    if (travel == toTravel + r) {
        changeDir();
        travel = 0;
    }

    return xy;
}

// The Spiral object takes ownership of the Piece pointers with std::move
Spiral::Spiral(int ring, int rect, std::vector<Piece*> pieces) : ring(ring), rect(rect), pieces(std::move(pieces)) {
    this->iterators.resize(0);
    for (int i=0; i < this->pieces.size(); ++i) 
        iterators.emplace_back(ring, rect);
    
    int side = (2 * ring) + 1;
    this->cells.resize(side);
    for (int i=0; i < side; ++i)
        this->cells[i].resize(side + rect);
}

// The Pieces must be deleted by the Spiral
Spiral::~Spiral() {
    for (Piece* piece : pieces)
        delete piece;
}

std::vector<std::vector<Cell>>* Spiral::getCells() {
    return &cells;
}

// Check if a given coordinate xy is a valid coordinate 
bool Spiral::insideRange(XY xy) {
    if (xy.x < 0 || xy.x > (2 * ring) + rect || xy.y < 0 || xy.y > (2 * ring)) 
        return false;
    else return true;
}

// Run the simulation
void Spiral::playGame() {
    // "Current color," determines whose turn it is
    int cColor = 0;
    // "Current XY," determines which cell is currently being considered
    XY cXy = iterators[cColor].getNext();

    while (true) {
        Cell* cell = &cells[cXy.y][cXy.x];
        int tries = 0;

        // The current cell is skipped if its occupied or unfriendly
        if (cell->isEmpty() && cell->isFriendly(pieces[cColor]->getEnemies())) {
            // Place the current player's piece on the cell
            auto attacked = cell->setPiece(pieces[cColor], cXy, ring, rect);
            // Update the targeted cells "attacked" status
            for (auto aXy : attacked)
                cells[aXy.y][aXy.x].setAttacker(cColor);

            // Only end turn after succesfully placing a piece
            cColor = (cColor + 1) % pieces.size();
        }

        // Hacky way of determining if the game's over
        do {
            // Get the current player's next cell to consider
            cXy = iterators[cColor].getNext();
            // If the iterator returns a cell that's out of range,
            // it means the current player reached the end of the board
            if (!insideRange(cXy)) {
                // Pass the turn to the next player and try again
                cColor = (cColor + 1) % pieces.size();
                tries++;
            }
            else break;
        } while (tries < pieces.size());
        // If every player passed their turn, the game's over
        if (tries == pieces.size()) break;
    }
}

// Unused function to print the simulation result on the console
void Spiral::printGame() {
    int side = (2 * ring) + 1;
    for (int i=0; i < side; ++i) {
        for (int j=0; j < side + rect; ++j) {
            Color color = cells[i][j].getColor();
            std::cout << color.toConsole() << "  ";
        }
        std::cout << CLR << std::endl;
    }
}