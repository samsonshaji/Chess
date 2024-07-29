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

vector<Move> Bishop::getAllMoves() const {
    vector<Move> moves;
    if (square == nullptr) return moves;
    
    addDirectionalMoves(moves, 1, 1);
    addDirectionalMoves(moves, 1, -1);
    addDirectionalMoves(moves, -1, 1);
    addDirectionalMoves(moves, -1, -1);
    return moves;
}

