#pragma once
#include "Piece.h"
#include <cmath>

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c) {}
    std::string getSymbol() const override {
        return color == WHITE ? "B" : "b";
    }

    bool isValidMove(int x1, int y1, int x2, int y2) override;
};
