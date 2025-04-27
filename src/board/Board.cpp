#include "Board.h"
#include "../pieces/Pawn.h"
#include "../pieces/Rook.h"
#include "../pieces/Knight.h"
#include "../pieces/Bishop.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"
#include <cstdlib> // for rand
#include <ctime>   // for time
#include <vector>
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
    grid[0][0] = new Rook(BLACK, this);
    grid[0][1] = new Knight(BLACK, this);
    grid[0][2] = new Bishop(BLACK, this);
    grid[0][3] = new Queen(BLACK, this);
    grid[0][4] = new King(BLACK, this);
    grid[0][5] = new Bishop(BLACK, this);
    grid[0][6] = new Knight(BLACK, this);
    grid[0][7] = new Rook(BLACK, this);

    // Black pawns (row 7 → grid[1])
    for (int i = 0; i < 8; ++i)
        grid[1][i] = new Pawn(BLACK, this);

    // White pawns (row 2 → grid[6])
    for (int i = 0; i < 8; ++i)
        grid[6][i] = new Pawn(WHITE, this);

    // White major pieces (row 1 → grid[7])
    grid[7][0] = new Rook(WHITE, this);
    grid[7][1] = new Knight(WHITE, this);
    grid[7][2] = new Bishop(WHITE, this);
    grid[7][3] = new Queen(WHITE, this);
    grid[7][4] = new King(WHITE, this);
    grid[7][5] = new Bishop(WHITE, this);
    grid[7][6] = new Knight(WHITE, this);
    grid[7][7] = new Rook(WHITE, this);


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

bool Board::isClearVertical(int col, int row1, int row2) const {
    int start = std::min(row1, row2) + 1;
    int end = std::max(row1, row2);
    for (int r = start; r < end; ++r) {
        if (grid[r][col] != nullptr)
            return false;
    }
    return true;
}

bool Board::isClearHorizontal(int row, int col1, int col2) const {
    int start = std::min(col1, col2) + 1;
    int end = std::max(col1, col2);
    for (int c = start; c < end; ++c) {
        if (grid[row][c] != nullptr)
            return false;
    }
    return true;
}

bool Board::isClearDiagonal(int x1, int y1, int x2, int y2) const {
    int dx = (x2 > x1) ? 1 : -1;
    int dy = (y2 > y1) ? 1 : -1;

    int r = x1 + dx;
    int c = y1 + dy;

    while (r != x2 && c != y2) {
        if (grid[r][c] != nullptr)
            return false;
        r += dx;
        c += dy;
    }
    return true;
}

std::pair<std::string, std::string> Board::generateRandomMove(Color aiColor) {
    std::vector<std::pair<std::string, std::string>> possibleMoves;
    for (int x1 = 0; x1 < 8; ++x1) {
        for (int y1 = 0; y1 < 8; ++y1) {
            Piece* piece = grid[x1][y1];
            if (piece && piece->getColor() == aiColor) {
                for (int x2 = 0; x2 < 8; ++x2) {
                    for (int y2 = 0; y2 < 8; ++y2) {
                        if (piece->isMoveValid(x1, y1, x2, y2)) {
                            Piece* target = grid[x2][y2];
                            if (!target || target->getColor() != aiColor) {
                                std::string from = std::string(1, 'a' + y1) + std::to_string(8 - x1);
                                std::string to = std::string(1, 'a' + y2) + std::to_string(8 - x2);
                                possibleMoves.push_back({from, to});
                            }
                        }
                    }
                }
            }
        }
    }

    if (possibleMoves.empty()) {
        return {"", ""}; // no moves available (e.g., checkmate/stalemate)
    }

    std::srand(std::time(nullptr));
    int randomIndex = rand() % possibleMoves.size();
    return possibleMoves[randomIndex];
}