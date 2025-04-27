#pragma once
#include <string>
#include "../pieces/Piece.h"
#include <utility> // for std::pair


class Board {
private:
    Piece* grid[8][8];

public:
    Board();
    ~Board();

    void display() const;
    void setupBoard();

    bool movePiece(int x1, int y1, int x2, int y2); // move using coordinates
    bool movePiece(const std::string& from, const std::string& to); // move using algebraic notation
    Piece* getPieceAt(const std::string& pos); // helper to get piece at a position
    bool isClearVertical(int col, int row1, int row2) const;
    bool isClearHorizontal(int row, int col1, int col2) const;
    bool isClearDiagonal(int x1, int y1, int x2, int y2) const;
    std::pair<std::string, std::string> generateRandomMove(Color aiColor);

};
