#include "../pieces/Pawn.h"

bool Pawn::isMoveValid(int x1, int y1, int x2, int y2) const {
    int direction = (color == WHITE) ? -1 : 1;
    // Move forward
    if (x2 == x1 + direction && y1 == y2) return true;
    // Move two squares forward from starting row
    if ((color == WHITE && x1 == 6 || color == BLACK && x1 == 1) && (x2 == x1 + 2 * direction) && (y1 == y2))
        return true;
    return false;
}
