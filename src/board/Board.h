#pragma once
#include <vector>
#include "../pieces/Piece.h"

class Board {
private:
    std::vector<std::vector<Piece*>> grid;
    std::pair<int, int> whiteKingPos;
    std::pair<int, int> blackKingPos;

public:
    Board();
    ~Board();
    void display();
    bool movePiece(int x1, int y1, int x2, int y2);
    bool moveKingTo(Color color, int x2, int y2);
};

