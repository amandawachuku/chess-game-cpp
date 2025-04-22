#include "Knight.h"

bool Knight::isValidMove(int x1, int y1, int x2, int y2) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
