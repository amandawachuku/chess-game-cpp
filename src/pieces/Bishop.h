#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Color c, Board* b) : Piece(c, b) {}

    char getSymbol() const override {
        return color == WHITE ? 'B' : 'b';
    }

    bool isMoveValid(int x1, int y1, int x2, int y2) const override;
};
