#pragma once
#include "Piece.h"
#include <cmath>

class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}
    std::string getSymbol() const override {
        return color == WHITE ? "Q" : "q";
    }

    bool isValidMove(int x1, int y1, int x2, int y2) override;
};
