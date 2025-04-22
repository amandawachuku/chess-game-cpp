#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color c) : Piece(c) {}
    std::string getSymbol() const override {
        return color == WHITE ? "R" : "r";
    }

    bool isValidMove(int x1, int y1, int x2, int y2) override;
};
