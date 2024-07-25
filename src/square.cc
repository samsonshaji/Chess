#include "square.h"

Square::Square(int x, int y) : x(x), y(y) {}

Square::Square() : x(-1), y(-1) {}

bool Square::isValid() const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}
