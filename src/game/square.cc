#include "square.h"
#include <iostream>

Square::Square(int x, int y) : x(x), y(y), piece(nullptr) {}

Square::~Square() {
    if (piece != nullptr) {
        // delete piece;
        piece = nullptr;
        board = nullptr;
    }
}

std::shared_ptr<Piece> Square::getPiece() const {
    return piece;
}

void Square::setPiece(std::shared_ptr<Piece> p) {
    this->piece = p;
    if (p == nullptr) return;

    // std::cout << "Setting piece on square " << x << " " << y << std::endl;
    p->setSquare(shared_from_this());
    // std::cout << "Setting board on piece" << std::endl;
    this->piece->setSquare(shared_from_this());
    p->setBoard(board);
}

void Square::setBoard(std::shared_ptr<Board> b) {
    board = b;
}

void Square::removePiece() {
    piece->setSquare(nullptr);
    piece = nullptr;
}

void Square::deletePiece() {
    // delete piece;
    piece = nullptr;
}

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}
