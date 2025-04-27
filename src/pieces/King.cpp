#include "../pieces/King.h"

bool King::isMoveValid(int x1, int y1, int x2, int y2) const {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    return (dx <= 1 && dy <= 1);
}
