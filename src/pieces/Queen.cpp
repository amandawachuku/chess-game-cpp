#include "Queen.h"

bool Queen::isValidMove(int x1, int y1, int x2, int y2) {
    return (x1 == x2 || y1 == y2) || (std::abs(x2 - x1) == std::abs(y2 - y1));
}
