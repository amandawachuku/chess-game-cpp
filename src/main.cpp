#include "board/Board.h"
#include "data/DatabaseManager.h"
#include <iostream>

int main() {
    Board board;
    DatabaseManager db("chess_game.db");

    if (!db.open() || !db.setupTables()) {
        std::cerr << "❌ Database setup failed. Exiting.\n";
        return 1;
    }

    int currentGameID = 1;
    int turnCounter = 1;

    while (true) {
        board.display();
        std::cout << "Enter move (e.g., e2 e4 or q to quit): ";
        std::string from, to;
        std::cin >> from;
        if (from == "q" || from == "quit") break;
        std::cin >> to;

        if (board.movePiece(from, to)) {
            Piece* movedPiece = board.getPieceAt(to);
            if (movedPiece) {
                std::string symbol = movedPiece->getSymbol();
                std::string color = movedPiece->getColor() == WHITE ? "White" : "Black";
                db.logMove(currentGameID, turnCounter, symbol, color, from, to);
                turnCounter++;
            }
        } else {
            std::cout << "❌ Invalid move.\n";
        }
    }

    db.close();
    return 0;
}
