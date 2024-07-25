#include "move.h"

Move::Move(Square from, Square to) : from(from), to(to) {}

Move::Move() : from(Square()), to(Square()) {}

MoveType Move::getMoveType() const {
    // Implement logic to determine the move type (e.g., normal move, castling, promotion, etc.)
    return MoveType::Normal;
}

void Move::execute() {
    // Implement logic to execute the move on the board
}

void Move::undo() {
    // Implement logic to undo the move on the board
}
