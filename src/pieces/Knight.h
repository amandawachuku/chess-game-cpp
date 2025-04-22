#pragma once
#include "Piece.h"
#include <cmath>

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}
    std::string getSymbol() const override {
        return color == WHITE ? "N" : "n";
    }

    bool isValidMove(int x1, int y1, int x2, int y2) override;
};
