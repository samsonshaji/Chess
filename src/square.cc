#include "square.h"

Square::Square(int x, int y) : x(x), y(y), piece(nullptr) {}

Square::Square() : x(-1), y(-1), piece(nullptr) {}

bool Square::isValid() const {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

Piece* Square::getPiece() const {
    return piece;
}

void Square::setPiece(Piece* p) {
    this->piece = p;
    // Update piece's square
    p->setSquare(this);
    p->setBoard(board);
}

void Square::setBoard(Board* b) {
    board = b;
}

void Square::removePiece() {
    piece = nullptr;
}

void Square::deletePiece() {
    delete piece;
    piece = nullptr;
}

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}
