#include "rook.h"

using namespace std;

Rook::Rook(Colour c) : Piece(c) {
    type = PieceType::rook;
    symbol = (c == Colour::White) ? 'R' : 'r';
}

vector<Move> Rook::getValidMoves() const {
    std::cout << "Rook::getValidMoves()" << std::endl;
    vector<Move> moves;
    
    // std::cout << "adding moves in direction 1, 0" << std::endl;
    addMovesInDirection(moves, 1, 0);
    // std::cout << "adding moves in direction -1, 0" << std::endl;
    addMovesInDirection(moves, -1, 0);
    // std::cout << "adding moves in direction 0, 1" << std::endl;
    addMovesInDirection(moves, 0, 1);
    // std::cout << "adding moves in direction 0, -1" << std::endl;
    addMovesInDirection(moves, 0, -1);

    // // white rook, kind side castling
    // if (colour == Colour::White && square->getX() == 0 && square->getY() == 0) {
    //     Square* targetSquare = board->getSquare(0, 2);
    //     if (targetSquare->getPiece() == nullptr) {
    //         Square* rookSquare = board->getSquare(0, 0);
    //         if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
    //             if (rookSquare->getPiece()->getColour() == Colour::White) {
    //                 moves.push_back(Move(square, targetSquare, MoveType::Castling));
    //             }
    //         }
    //     }
    // }

    // // white rook, queen side castling
    // if (colour == Colour::White && square->getX() == 0 && square->getY() == 7) {
    //     Square* targetSquare = board->getSquare(0, 6);
    //     if (targetSquare->getPiece() == nullptr) {
    //         Square* rookSquare = board->getSquare(0, 7);
    //         if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
    //             if (rookSquare->getPiece()->getColour() == Colour::White) {
    //                 moves.push_back(Move(square, targetSquare, MoveType::Castling));
    //             }
    //         }
    //     }
    // }

    // // black rook, king side castling
    // if (colour == Colour::Black && square->getX() == 7 && square->getY() == 0) {
    //     Square* targetSquare = board->getSquare(7, 2);
    //     if (targetSquare->getPiece() == nullptr) {
    //         Square* rookSquare = board->getSquare(7, 0);
    //         if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
    //             if (rookSquare->getPiece()->getColour() == Colour::Black) {
    //                 moves.push_back(Move(square, targetSquare, MoveType::Castling));
    //             }
    //         }
    //     }
    // }

    // // black rook, queen side castling
    // if (colour == Colour::Black && square->getX() == 7 && square->getY() == 7) {
    //     Square* targetSquare = board->getSquare(7, 6);
    //     if (targetSquare->getPiece() == nullptr) {
    //         Square* rookSquare = board->getSquare(7, 7);
    //         if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
    //             if (rookSquare->getPiece()->getColour() == Colour::Black) {
    //                 moves.push_back(Move(square, targetSquare, MoveType::Castling));
    //             }
    //         }
    //     }
    // }
    return moves;
}