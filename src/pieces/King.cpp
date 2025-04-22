#include "King.h"

bool King::isValidMove(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) <= 1 && std::abs(y2 - y1) <= 1;
}
