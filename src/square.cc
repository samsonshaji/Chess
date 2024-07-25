#include "square.h"

Square::Square(int x, int y) : x(x), y(y), piece(nullptr) {}

Square::Square() : x(-1), y(-1), piece(nullptr) {}

bool Square::isValid() const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

Piece* Square::getPiece() const {
    return piece;
}

void Square::setPiece(Piece* piece) {
    this->piece = piece;
}
