#include "move.h"

Move::Move(Square* f, Square* t) : from(f), to(t) {}

Move::Move(Square* f, Square* t, MoveType mt) : from(f), to(t), type(mt) {}

MoveType Move::getMoveType() const {
    return type;
}

void Move::setType(MoveType t) {
    type = t;
}

void Move::execute() {
    // Implement logic to execute the move on the board
}

void Move::undo() {
    // Implement logic to undo the move on the board
}
