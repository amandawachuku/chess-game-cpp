#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(Color c, Board* b) : Piece(c, b) {}

    char getSymbol() const override {
        return color == WHITE ? 'N' : 'n';
    }

    bool isMoveValid(int x1, int y1, int x2, int y2) const override;
};
