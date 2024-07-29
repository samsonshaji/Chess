#include "move.h"

Move::Move() {}

Move::Move(Square* f, Square* t) : from(f), to(t) {}

MoveType Move::getMoveType() const {
    return type;
}

void Move::setMoveType(MoveType t) {
    type = t;
}

MoveType Move::getPawnSecondary() const {
    return pawnSecondary;
}

void Move::setPawnSecondary(MoveType t) {
    pawnSecondary = t;
}

Square* Move::getFrom() const {
    return (from) ? from : nullptr;
}

Square* Move::getTo() const {
    return (to) ? to : nullptr;
}

char Move::getPromotedTo() const {
    return promotedTo;
}

void Move::setPromotedTo(char c) {
    promotedTo = c;
}

Move& Move::operator=(const Move& m) {
    from = m.from;
    to = m.to;
    type = m.type;
    promotedTo = m.promotedTo;
    pawnSecondary = m.pawnSecondary;
    return *this;
}

bool Move::operator==(const Move& m) const {
    return from->getX() == m.from->getX() && from->getY() == m.from->getY() && to->getX() == m.to->getX() && to->getY() == m.to->getY();
}