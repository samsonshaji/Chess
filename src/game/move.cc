#include "move.h"

Move::Move(Square* f, Square* t) : from(f), to(t) {}

Move::Move(Square* f, Square* t, MoveType mt) : from(f), to(t), type(mt) {}

MoveType Move::getMoveType() const {
    return type;
}

void Move::setMoveType(MoveType t) {
    type = t;
}

Square* Move::getFrom() const {
    return from;
}

Square* Move::getTo() const {
    return to;
}

Piece* Move::getCapturedPiece() const {
    return capturedPiece;
}

void Move::setCapturedPiece(Piece* piece) {
    capturedPiece = piece;
}

void Move::execute() {
    
}
