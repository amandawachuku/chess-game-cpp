#include "../pieces/Queen.h"
#include "../board/Board.h"

bool Queen::isMoveValid(int x1, int y1, int x2, int y2) const {
    if (x1 == x2) return board->isClearHorizontal(x1, y1, y2);
    if (y1 == y2) return board->isClearVertical(y1, x1, x2);
    if (abs(x2 - x1) == abs(y2 - y1)) return board->isClearDiagonal(x1, y1, x2, y2);
    return false;
}
