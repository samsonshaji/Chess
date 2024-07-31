#include "square.h"
#include <iostream>

Square::Square(int x, int y) : x(x), y(y), piece(nullptr) {}

Square::~Square() {
    std::cout << "Square destructor called" << std::endl;
    if (piece != nullptr) {
        delete piece;
        piece = nullptr;
        board = nullptr;
    }
}

Piece* Square::getPiece() const {
    return piece;
}

void Square::setPiece(Piece* p) {
    this->piece = p;
    if (p == nullptr) return;
    p->setSquare(this);
    p->setBoard(board);
}

void Square::setBoard(Board* b) {
    board = b;
}

void Square::removePiece() {
    piece->setSquare(nullptr);
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
