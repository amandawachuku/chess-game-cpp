#include "../pieces/Bishop.h"
#include "../board/Board.h"

bool Bishop::isMoveValid(int x1, int y1, int x2, int y2) const {
    if (abs(x2 - x1) == abs(y2 - y1)) {
        return board->isClearDiagonal(x1, y1, x2, y2);
    }
    return false;
}
