#pragma once
#include <string>

enum Color { WHITE, BLACK };

class Piece {
protected:
    Color color;

public:
    Piece(Color c) : color(c) {}
    virtual ~Piece() = default;

    Color getColor() const { return color; }
    virtual std::string getSymbol() const = 0;
    virtual bool isValidMove(int x1, int y1, int x2, int y2) = 0;
};
