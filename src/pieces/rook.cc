#include "rook.h"

using namespace std;

Rook::Rook(Colour c) : Piece(c) {
    type = PieceType::rook;
    symbol = (c == Colour::White) ? 'R' : 'r';
}

Rook::~Rook() {
    cout << "Rook destructor called" << endl;
}

vector<Move> Rook::getValidMoves() const {
    vector<Move> moves;
    
    addMovesInDirection(moves, 1, 0);
    addMovesInDirection(moves, -1, 0);
    addMovesInDirection(moves, 0, 1);
    addMovesInDirection(moves, 0, -1);
    return moves;
}