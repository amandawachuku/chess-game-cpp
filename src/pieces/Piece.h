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

#define DEFINE_PIECE(NAME, SYMBOL_W, SYMBOL_B, VALID) \
class NAME : public Piece { \
public: \
    NAME(Color c) : Piece(c) {} \
    std::string getSymbol() const override { return color == WHITE ? SYMBOL_W : SYMBOL_B; } \
    bool isValidMove(int x1, int y1, int x2, int y2) override { VALID } \
};

DEFINE_PIECE(King,   "K", "k", return abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1;)
DEFINE_PIECE(Queen,  "Q", "q", return x1 == x2 || y1 == y2 || abs(x2 - x1) == abs(y2 - y1);)
DEFINE_PIECE(Rook,   "R", "r", return x1 == x2 || y1 == y2;)
DEFINE_PIECE(Bishop, "B", "b", return abs(x2 - x1) == abs(y2 - y1);)
DEFINE_PIECE(Knight, "N", "n", return (abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2);)
DEFINE_PIECE(Pawn,   "P", "p", \
    int dir = (color == WHITE) ? 1 : -1; \
    if (x2 == x1 + dir && y2 == y1) return true; \
    if ((color == WHITE && x1 == 1 && x2 == 3 && y2 == y1) || (color == BLACK && x1 == 6 && x2 == 4 && y2 == y1)) return true; \
    return false;)

#undef DEFINE_PIECE
