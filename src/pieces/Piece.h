#pragma once
#include <string>

class Board; // forward declaration

enum Color { WHITE, BLACK };

class Piece {
protected:
    Color color;
    Board* board;  // 🆕 Pointer to the Board

public:
    Piece(Color c, Board* b) : color(c), board(b) {}
    virtual ~Piece() {}

    Color getColor() const { return color; }
    virtual char getSymbol() const = 0;
    virtual bool isMoveValid(int x1, int y1, int x2, int y2) const = 0;
};

