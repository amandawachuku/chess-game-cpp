#include "../pieces/Knight.h"

bool Knight::isMoveValid(int x1, int y1, int x2, int y2) const {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
