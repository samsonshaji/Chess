#include "piece.h"
#include "square.h"
#include "board.h"
#include <vector>

using namespace std;

Piece::~Piece() {
    square = nullptr;
    board = nullptr;
}

PieceType Piece::getPieceType() const {
    return type;
}

Colour Piece::getColour() const {
    return colour;
}

Piece::Piece(Colour c) : colour(c) {}

Square *Piece::getSquare() const {
    return square;
}

void Piece::setSquare(Square *s) {
    square = s;
}

void Piece::setBoard(Board *b) {
    board = b;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool m) {
    hasMoved = m;
}

char Piece::getSymbol() const {
    return symbol;
}

bool Piece::operator==(const Piece &other) const {
    return type == other.type && square->getX() == other.square->getX() && square->getY() == other.square->getY();
}