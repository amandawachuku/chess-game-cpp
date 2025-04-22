#include "Bishop.h"

bool Bishop::isValidMove(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) == std::abs(y2 - y1);
}
