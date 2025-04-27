#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Color c, Board* b) : Piece(c, b) {}

    char getSymbol() const override {
        return color == WHITE ? 'Q' : 'q';
    }

    bool isMoveValid(int x1, int y1, int x2, int y2) const override;
};
