#include "knight.h"
#include "move.h"
#include "square.h"
#include "board.h"
#include "movetype.h"
#include <vector>

using namespace std;

Knight::Knight(Colour c) : Piece(c) {
    type = PieceType::Knight;
    symbol = (c == Colour::White) ? 'N' : 'n';
}

//fill the vector with all possible Moves a knight can make at any given time
vector<Move> Knight::getValidMoves() const {
    vector<Move> validMoves;
    
    validMoves.push_back(Move(square, board->getSquare(square->getX() + 2, square->getY() + 1), MoveType::Normal));
}