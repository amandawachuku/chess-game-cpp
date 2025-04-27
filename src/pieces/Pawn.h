#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(Color c, Board* b) : Piece(c, b) {}

    char getSymbol() const override {
        return color == WHITE ? 'P' : 'p';
    }

    bool isMoveValid(int x1, int y1, int x2, int y2) const override;
};
