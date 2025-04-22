#include "Board.h"
#include "../pieces/King.h"
#include "../pieces/Queen.h"
#include "../pieces/Rook.h"
#include "../pieces/Bishop.h"
#include "../pieces/Knight.h"
#include "../pieces/Pawn.h"
#include <iostream>

Board::Board() {
    grid.resize(8, std::vector<Piece*>(8, nullptr));

    grid[0][0] = new Rook(WHITE);
    grid[0][1] = new Knight(WHITE);
    grid[0][2] = new Bishop(WHITE);
    grid[0][3] = new Queen(WHITE);
    grid[0][4] = new King(WHITE); whiteKingPos = {0, 4};
    grid[0][5] = new Bishop(WHITE);
    grid[0][6] = new Knight(WHITE);
    grid[0][7] = new Rook(WHITE);
    for (int i = 0; i < 8; ++i) grid[1][i] = new Pawn(WHITE);

    grid[7][0] = new Rook(BLACK);
    grid[7][1] = new Knight(BLACK);
    grid[7][2] = new Bishop(BLACK);
    grid[7][3] = new Queen(BLACK);
    grid[7][4] = new King(BLACK); blackKingPos = {7, 4};
    grid[7][5] = new Bishop(BLACK);
    grid[7][6] = new Knight(BLACK);
    grid[7][7] = new Rook(BLACK);
    for (int i = 0; i < 8; ++i) grid[6][i] = new Pawn(BLACK);
}

Board::~Board() {
    for (auto& row : grid)
        for (auto& piece : row)
            delete piece;
}

void Board::display() {
    for (int i = 7; i >= 0; --i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 8; ++j)
            std::cout << (grid[i][j] ? grid[i][j]->getSymbol() : ".") << " ";
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h\n";
}

bool Board::movePiece(int x1, int y1, int x2, int y2) {
    Piece* p = grid[x1][y1];
    if (!p || !p->isValidMove(x1, y1, x2, y2)) return false;
    delete grid[x2][y2];
    grid[x2][y2] = p;
    grid[x1][y1] = nullptr;
    if (p->getSymbol() == "K") whiteKingPos = {x2, y2};
    if (p->getSymbol() == "k") blackKingPos = {x2, y2};
    return true;
}

bool Board::moveKingTo(Color color, int x2, int y2) {
    std::pair<int, int> current = (color == WHITE) ? whiteKingPos : blackKingPos;
    return movePiece(current.first, current.second, x2, y2);
}

