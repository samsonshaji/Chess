#include "queen.h"


Queen::Queen(Colour c) : Piece(c) {
    type = PieceType::queen;
    symbol = (c == Colour::White) ? 'Q' : 'q';
}

Queen::~Queen() {
    cout << "Queen destructor called" << endl;
}

std::vector<Move> Queen::getValidMoves() const {
    std::vector<Move> moves;
    addMovesInDirection(moves, 1, 0);
    addMovesInDirection(moves, -1, 0);
    addMovesInDirection(moves, 0, 1);
    addMovesInDirection(moves, 0, -1);
    addMovesInDirection(moves, 1, 1);
    addMovesInDirection(moves, 1, -1);
    addMovesInDirection(moves, -1, 1);
    addMovesInDirection(moves, -1, -1);
    return moves;
}