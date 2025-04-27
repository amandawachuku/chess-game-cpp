#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color c, Board* b) : Piece(c, b) {}

    char getSymbol() const override {
        return color == WHITE ? 'R' : 'r';
    }

    bool isMoveValid(int x1, int y1, int x2, int y2) const override;
};
