#include "move.h"

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
    return *this;
}

bool Move::operator==(const Move& m) const {
    return from == m.from && to == m.to;
}