#include <iostream>
#include "board/Board.h"

int main() {
    Board board;
    bool whiteTurn = true;

    std::string from, to;
    while (true) {
        board.display();
        std::cout << (whiteTurn ? "White" : "Black") << "'s move (e.g., e2 e4): ";
        std::cin >> from;

        if (from == "exit") break;

        std::cin >> to;
        if (to == "exit") break;

        if (from.length() != 2 || to.length() != 2 ||
            from[0] < 'a' || from[0] > 'h' || from[1] < '1' || from[1] > '8' ||
            to[0] < 'a' || to[0] > 'h' || to[1] < '1' || to[1] > '8') {
            std::cout << "Invalid input format. Try again (e.g., e2 e4).\n";
            continue;
        }

        int y1 = from[0] - 'a';
        int x1 = from[1] - '1';
        int y2 = to[0] - 'a';
        int x2 = to[1] - '1';

        if (board.movePiece(x1, y1, x2, y2)) {
            whiteTurn = !whiteTurn;
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
