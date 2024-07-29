#include "queen.h"


Queen::Queen(Colour c) : Piece(c) {
    type = PieceType::queen;
    symbol = (c == Colour::White) ? 'Q' : 'q';
}

std::vector<Move> Queen::getValidMoves() const {
    // std::cout << "Queen" << std::endl;
    std::vector<Move> moves;
    // std::cout << "adding direction 1 0" << std::endl;
    addMovesInDirection(moves, 1, 0);
    // std::cout << "adding direction -1 0" << std::endl;
    addMovesInDirection(moves, -1, 0);
    // std::cout << "adding direction 0 1" << std::endl;
    addMovesInDirection(moves, 0, 1);
    // std::cout << "adding direction 0 -1" << std::endl;
    addMovesInDirection(moves, 0, -1);
    // std::cout << "adding direction 1 1" << std::endl;
    addMovesInDirection(moves, 1, 1);
    // std::cout << "adding direction 1 -1" << std::endl;
    addMovesInDirection(moves, 1, -1);
    // std::cout << "adding direction -1 1" << std::endl;
    addMovesInDirection(moves, -1, 1);
    // std::cout << "adding direction -1 -1" << std::endl;
    addMovesInDirection(moves, -1, -1);
    return moves;
}