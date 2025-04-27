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

    bool isHumanWhite = true;
    int currentGameID = db.startNewGame("Player1", "Player2");
    int turnCounter = 1;
    bool whiteTurn = true;

    while (true) {
        board.display();
        std::cout << (whiteTurn ? "White's turn. " : "Black's turn. ");
        std::string from, to;

        if ((whiteTurn && isHumanWhite) || (!whiteTurn && !isHumanWhite)) {
            // Human move
            std::cout << "Enter move (e.g., e2 e4 or q to quit): ";
            std::cin >> from;
            if (from == "q" || from == "quit") {
                std::string winner = whiteTurn ? "Black" : "White";
                db.endGame(currentGameID, winner);
                db.close();
                break;
            }
            std::cin >> to;
        } else {
            // AI move
            auto move = board.generateRandomMove(whiteTurn ? WHITE : BLACK);
            from = move.first;
            to = move.second;
            std::cout << "🤖 AI moves from " << from << " to " << to << std::endl;
        }

        // ✅ Check if correct color is moving
        Piece* selectedPiece = board.getPieceAt(from);
        if (!selectedPiece) {
            std::cout << "❌ No piece at " << from << ". Try again.\n";
            continue;
        }
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
        
                if (!whiteTurn) {
                    turnCounter++; // Only increment after Black moves
                }
                whiteTurn = !whiteTurn;
            }
        }
         else {
            std::cout << "❌ Invalid move.\n";
        }
    }

    db.close();
    return 0;
}
