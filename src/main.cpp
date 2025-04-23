#include <iostream>
#include "board/Board.h"
#include "data/DatabaseManager.h"

int main() {
    DatabaseManager db("chess_game.db");

    if (!db.open() || !db.setupTables()) {
        std::cerr << "❌ Database setup failed. Exiting.\n";
        return 1;
    }

    // 🔁 Simulate a test move log
    int gameID = 1;
    int turn = 1;
    std::string piece = "Pawn";
    std::string color = "White";
    std::string from = "e2";
    std::string to = "e4";

    db.logMove(gameID, turn, piece, color, from, to);

    db.close();
    return 0;
}
