#include "rook.h"

using namespace std;

Rook::Rook(Colour c) : Piece(c) {
    type = PieceType::rook;
    symbol = (c == Colour::White) ? 'R' : 'r';
}

void Rook::addStraightMoves(vector<Move>& moves, int xDir, int yDir) const {
    int x = square->getX() + xDir;
    int y = square->getY() + yDir;

    while (x >= 0 && x < 8 && y >= 0 && y < 8) {

        Square* targetSquare = board->getSquare(x, y);
        Piece *thisPiece = targetSquare->getPiece();


        if (targetSquare->getPiece() != nullptr) {
            if (targetSquare->getPiece()->getColour() != colour) {
                moves.push_back(Move(square, targetSquare));
            }
            break;
        }

        std::cout << "Pushing move" << std::endl;
        moves.push_back(Move(square, targetSquare));
        x += xDir;
        y += yDir;
    }
}

vector<Move> Rook::getValidMoves() const {
    vector<Move> moves;
    addStraightMoves(moves, 1, 0);
    addStraightMoves(moves, -1, 0);
    addStraightMoves(moves, 0, 1);
    addStraightMoves(moves, 0, -1);

    // white rook, kind side castling
    if (colour == Colour::White && square->getX() == 0 && square->getY() == 0) {
        Square* targetSquare = board->getSquare(0, 2);
        if (targetSquare->getPiece() == nullptr) {
            Square* rookSquare = board->getSquare(0, 0);
            if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
                if (rookSquare->getPiece()->getColour() == Colour::White) {
                    moves.push_back(Move(square, targetSquare, MoveType::Castling));
                }
            }
        }
    }

    // white rook, queen side castling
    if (colour == Colour::White && square->getX() == 0 && square->getY() == 7) {
        Square* targetSquare = board->getSquare(0, 6);
        if (targetSquare->getPiece() == nullptr) {
            Square* rookSquare = board->getSquare(0, 7);
            if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
                if (rookSquare->getPiece()->getColour() == Colour::White) {
                    moves.push_back(Move(square, targetSquare, MoveType::Castling));
                }
            }
        }
    }

    // black rook, king side castling
    if (colour == Colour::Black && square->getX() == 7 && square->getY() == 0) {
        Square* targetSquare = board->getSquare(7, 2);
        if (targetSquare->getPiece() == nullptr) {
            Square* rookSquare = board->getSquare(7, 0);
            if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
                if (rookSquare->getPiece()->getColour() == Colour::Black) {
                    moves.push_back(Move(square, targetSquare, MoveType::Castling));
                }
            }
        }
    }

    // black rook, queen side castling
    if (colour == Colour::Black && square->getX() == 7 && square->getY() == 7) {
        Square* targetSquare = board->getSquare(7, 6);
        if (targetSquare->getPiece() == nullptr) {
            Square* rookSquare = board->getSquare(7, 7);
            if (rookSquare->getPiece() != nullptr && rookSquare->getPiece()->getPieceType() == PieceType::rook) {
                if (rookSquare->getPiece()->getColour() == Colour::Black) {
                    moves.push_back(Move(square, targetSquare, MoveType::Castling));
                }
            }
        }
    }

    std::cout << "Rook: " << moves.size() << std::endl;
    return moves;
}