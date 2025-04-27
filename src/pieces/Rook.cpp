#include "../pieces/Rook.h"
#include "../board/Board.h"

bool Rook::isMoveValid(int x1, int y1, int x2, int y2) const {
    if (x1 == x2) return board->isClearHorizontal(x1, y1, y2);
    if (y1 == y2) return board->isClearVertical(y1, x1, x2);
    return false;
}
