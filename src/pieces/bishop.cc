#include "bishop.h"
#include "move.h"
#include "square.h"
#include "board.h"
#include "movetype.h"
#include <vector>

using namespace std;

Bishop::Bishop(Colour c) : Piece(c) {
    type = PieceType::bishop;
    symbol = (c == Colour::White) ? 'B' : 'b';
}

Bishop::~Bishop() {
}


vector<Move> Bishop::getValidMoves() const {
    vector<Move> moves;
    addMovesInDirection(moves, 1, 1);
    addMovesInDirection(moves, 1, -1);
    addMovesInDirection(moves, -1, 1);
    addMovesInDirection(moves, -1, -1);
    return moves;
}
