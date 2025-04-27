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
    bool whiteTurn = true;

    while (true) {
        board.display();
        std::cout << (whiteTurn ? "White's turn. " : "Black's turn. ");
        std::cout << "Enter move (e.g., e2 e4 or q to quit): ";
        std::string from, to;
        std::cin >> from;
        if (from == "q" || from == "quit") break;
        std::cin >> to;

        // ✅ Check if correct color is moving
        Piece* selectedPiece = board.getPieceAt(from);
        if ((whiteTurn && selectedPiece->getColor() != WHITE) ||
            (!whiteTurn && selectedPiece->getColor() != BLACK)) {
            std::cout << "❌ It's " << (whiteTurn ? "White" : "Black") << "'s turn. Please move your own piece.\n";
            continue;
        }

        if (board.movePiece(from, to)) {
            Piece* movedPiece = board.getPieceAt(to);
            if (movedPiece) {
                std::string symbol(1, movedPiece->getSymbol());
                std::string color = movedPiece->getColor() == WHITE ? "White" : "Black";
                db.logMove(currentGameID, turnCounter, symbol, color, from, to);
                turnCounter++;

                whiteTurn = !whiteTurn;//change whose turn it is after each successful move
            }
            
        } else {
            std::cout << "❌ Invalid move.\n";
        }
    }

    db.close();
    return 0;
}
