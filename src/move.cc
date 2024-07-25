#include "move.h"

Move::Move() : from(Square()), to(Square()) {}

Move::Move(Square from, Square to) : from(from), to(to) {}

// TODO
MoveType Move::getMoveType() const {
    if (to.getPiece() != PieceType::Empty) {
        return MoveType::Capture;
    }
    return MoveType::Normal;
}

void Move::execute() {
    to.setPiece(from.getPiece());
    from.setPiece(PieceType::Empty);
}

void Move::undo() {
    from.setPiece(to.getPiece());
    to.setPiece(PieceType::Empty);
}
