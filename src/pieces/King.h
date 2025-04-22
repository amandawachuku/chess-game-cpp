#pragma once
#include "Piece.h"
#include <cmath>

class King : public Piece {
public:
    King(Color c) : Piece(c) {}
    std::string getSymbol() const override {
        return color == WHITE ? "K" : "k";
    }

    bool isValidMove(int x1, int y1, int x2, int y2) override;
};
