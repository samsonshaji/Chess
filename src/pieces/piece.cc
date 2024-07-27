#include "piece.h"
#include "square.h"
#include "board.h"
#include <vector>

using namespace std;

Piece::~Piece() {}

PieceType Piece::getPieceType() const {
    return type;
}

Colour Piece::getColour() const {
    return colour;
}

Piece::Piece(Colour c) : colour(c) {}

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