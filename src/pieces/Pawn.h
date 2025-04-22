#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}
    std::string getSymbol() const override {
        return color == WHITE ? "P" : "p";
    }

    bool isValidMove(int x1, int y1, int x2, int y2) override;
};
