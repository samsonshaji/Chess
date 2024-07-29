#include "queen.h"


Queen::Queen(Colour c) : Piece(c) {
    type = PieceType::queen;
    symbol = (c == Colour::White) ? 'Q' : 'q';
}

std::vector<Move> Queen::getAllMoves() const {
    std::vector<Move> moves;
    if(!square) return moves;
    addDirectionalMoves(moves, 1, 1);
    addDirectionalMoves(moves, 1, -1);
    addDirectionalMoves(moves, -1, 1);
    addDirectionalMoves(moves, -1, -1);
    addDirectionalMoves(moves, 1, 0);
    addDirectionalMoves(moves, -1, 0);
    addDirectionalMoves(moves, 0, 1);
    addDirectionalMoves(moves, 0, -1);
    return moves;
}