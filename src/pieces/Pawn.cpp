#include "Pawn.h"

bool Pawn::isValidMove(int x1, int y1, int x2, int y2) {
    int direction = (color == WHITE) ? 1 : -1;

    // Single step forward
    if (x2 == x1 + direction && y2 == y1)
        return true;

    // Double step forward from starting row
    if (color == WHITE && x1 == 1 && x2 == 3 && y2 == y1)
        return true;

    if (color == BLACK && x1 == 6 && x2 == 4 && y2 == y1)
        return true;

    return false;
}
