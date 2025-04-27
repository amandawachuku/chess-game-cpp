#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(Color c, Board* b) : Piece(c, b) {}

    char getSymbol() const override {
        return color == WHITE ? 'K' : 'k';
    }

    bool isMoveValid(int x1, int y1, int x2, int y2) const override;
};
