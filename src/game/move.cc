#include "move.h"
#include <iostream>

Move::Move() {}

Move::Move(Square* f, Square* t) : from(f), to(t) {}

Move::Move(Square* f, Square* t, MoveType mt) : from(f), to(t), type(mt) {}

Move::Move(Square* f, Square* t, MoveType mt, char p) : from(f), to(t), type(mt), promotedTo(p) {}

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

char Move::getPromotedTo() const {
    return promotedTo;
}

void Move::setPromotedTo(char p) {
    promotedTo = p;
}

Piece* Move::getPromotedPawn() {
    return promotedPawn;
}

void Move::setPromotedPawn(Piece* piece) {
    this->promotedPawn = piece;
}

Move::Move(const Move& m) : from(m.from), to(m.to), type(m.type), promotedTo(m.promotedTo), capturedPiece(m.capturedPiece), promotedPawn(m.promotedPawn) {}

Move& Move::operator=(const Move& m) {
    from = m.from;
    to = m.to;
    type = m.type;
    capturedPiece = m.capturedPiece;
    promotedTo = m.promotedTo;
    promotedPawn = m.promotedPawn;
    return *this;
}

bool Move::operator==(const Move& m) const {
    return from->getX() == m.from->getX() && from->getY() == m.from->getY() && to->getX() == m.to->getX() && to->getY() == m.to->getY();
}