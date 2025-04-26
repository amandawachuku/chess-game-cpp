#include "Board.h"
#include "../pieces/Pawn.h"
#include "../pieces/Rook.h"
#include "../pieces/Knight.h"
#include "../pieces/Bishop.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"

#include <iostream>
#include <cctype>


Board::Board() {
    setupBoard();
}

Board::~Board() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            delete grid[r][c];
            grid[r][c] = nullptr;
        }
    }
}

void Board::setupBoard() {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            grid[r][c] = nullptr;

    // Black major pieces (row 8 → grid[0])
    grid[0][0] = new Rook(BLACK);
    grid[0][1] = new Knight(BLACK);
    grid[0][2] = new Bishop(BLACK);
    grid[0][3] = new Queen(BLACK);
    grid[0][4] = new King(BLACK);
    grid[0][5] = new Bishop(BLACK);
    grid[0][6] = new Knight(BLACK);
    grid[0][7] = new Rook(BLACK);

    // Black pawns (row 7 → grid[1])
    for (int i = 0; i < 8; ++i)
        grid[1][i] = new Pawn(BLACK);

    // White pawns (row 2 → grid[6])
    for (int i = 0; i < 8; ++i)
        grid[6][i] = new Pawn(WHITE);

    // White major pieces (row 1 → grid[7])
    grid[7][0] = new Rook(WHITE);
    grid[7][1] = new Knight(WHITE);
    grid[7][2] = new Bishop(WHITE);
    grid[7][3] = new Queen(WHITE);
    grid[7][4] = new King(WHITE);
    grid[7][5] = new Bishop(WHITE);
    grid[7][6] = new Knight(WHITE);
    grid[7][7] = new Rook(WHITE);
}

void Board::display() const {
    std::cout << "  a b c d e f g h\n";
    for (int r = 0; r < 8; ++r) {
        std::cout << 8 - r << " ";
        for (int c = 0; c < 8; ++c) {
            if (grid[r][c])
                std::cout << grid[r][c]->getSymbol() << " ";
            else
                std::cout << ". ";
        }
        std::cout << 8 - r << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}

bool Board::movePiece(int x1, int y1, int x2, int y2) {
    if (grid[x1][y1] == nullptr) {
        std::cout << "❌ No piece at starting square.\n";
        return false;
    }

    grid[x2][y2] = grid[x1][y1];
    grid[x1][y1] = nullptr;
    return true;
}

bool Board::movePiece(const std::string& from, const std::string& to) {
    if (from.length() != 2 || to.length() != 2)
        return false;

    int fromCol = std::tolower(from[0]) - 'a';
    int fromRow = 8 - (from[1] - '0');
    int toCol = std::tolower(to[0]) - 'a';
    int toRow = 8 - (to[1] - '0');

    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 ||
        toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7)
        return false;

    return movePiece(fromRow, fromCol, toRow, toCol);
}

Piece* Board::getPieceAt(const std::string& pos) {
    if (pos.length() != 2)
        return nullptr;

    int col = std::tolower(pos[0]) - 'a';
    int row = 8 - (pos[1] - '0');

    if (row < 0 || row > 7 || col < 0 || col > 7)
        return nullptr;

    return grid[row][col];
}
