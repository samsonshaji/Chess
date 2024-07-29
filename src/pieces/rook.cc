#include "rook.h"

using namespace std;

Rook::Rook(Colour c) : Piece(c) {
    type = PieceType::rook;
    symbol = (c == Colour::White) ? 'R' : 'r';
}

vector<Move> Rook::getAllMoves() const {
    vector<Move> moves;
    if (!square) return moves;
    addDirectionalMoves(moves, 1, 0);
    addDirectionalMoves(moves, -1, 0);
    addDirectionalMoves(moves, 0, 1);
    addDirectionalMoves(moves, 0, -1);
    return moves;
}