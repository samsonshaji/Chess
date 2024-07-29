#include "pawn.h"
#include "move.h"
#include "square.h"
#include "board.h"
#include "movetype.h"
#include <vector>

using namespace std;

Pawn::Pawn(Colour c) : Piece(c) {
    type = PieceType::pawn;
    symbol = (c == Colour::White) ? 'P' : 'p';
}

std::vector<Move> Pawn::getAllMoves() const {
    std::vector<Move> validMoves;

    if (!square) return validMoves;

    int curX = square->getX();
    int curY = square->getY();
    int direction = (colour == Colour::White) ? 1 : -1;

    if (curY + direction >= 0 && curY + direction < 8) {
        if(colour == Colour::White) {
            if (board->getSquare(curX, curY + direction)->getPiece() == nullptr) {
                Move m = Move(square, board->getSquare(curX, curY + direction));
                if (curY + direction == 7) {
                    m.setMoveType(MoveType::Promotion);
                } else {
                    m.setMoveType(MoveType::Normal);
                }
                validMoves.push_back(m);
            }
            if (curY == 1 && board->getSquare(curX, curY + 2 * direction)->getPiece() == nullptr && board->getSquare(curX, curY + direction)->getPiece() == nullptr && !getHasMoved()){
                Move m = Move(square, board->getSquare(curX, curY + 2 * direction));
                m.setMoveType(MoveType::DoublePawn);
                validMoves.push_back(m);
            }
            if (curX - 1 >= 0 && board->getSquare(curX - 1, curY + direction)->getPiece() != nullptr && board->getSquare(curX - 1, curY + direction)->getPiece()->getColour() != colour) {
                Move m = Move(square, board->getSquare(curX - 1, curY + direction));
                m.setMoveType(MoveType::Capture);
                if (curY + direction == 7) {
                    m.setPawnSecondary(MoveType::Promotion);
                } 
                validMoves.push_back(m);
            }
            if (curX + 1 < 8 && board->getSquare(curX + 1, curY + direction)->getPiece() != nullptr && board->getSquare(curX + 1, curY + direction)->getPiece()->getColour() != colour) {
                Move m = Move(square, board->getSquare(curX + 1, curY + direction));
                m.setMoveType(MoveType::Capture);
                if (curY + direction == 7) {
                    m.setPawnSecondary(MoveType::Promotion);
                } 
                validMoves.push_back(m);
            }
            if (curY == 4) {
                if (curX - 1 >= 0 && board->getSquare(curX - 1, curY)->getPiece() != nullptr && board->getSquare(curX - 1, curY)->getPiece()->getPieceType() == PieceType::pawn && board->getSquare(curX - 1, curY)->getPiece()->getColour() != colour && board->getSquare(curX - 1, curY)->getPiece()->getEnPassantable()) {
                    Move m = Move(square, board->getSquare(curX - 1, curY + direction));
                    m.setMoveType(MoveType::EnPassant);
                    validMoves.push_back(m);
                }
                if (curX + 1 < 8 && board->getSquare(curX + 1, curY)->getPiece() != nullptr && board->getSquare(curX + 1, curY)->getPiece()->getPieceType() == PieceType::pawn && board->getSquare(curX + 1, curY)->getPiece()->getColour() != colour && board->getSquare(curX + 1, curY)->getPiece()->getEnPassantable()) {
                    Move m = Move(square, board->getSquare(curX + 1, curY + direction));
                    m.setMoveType(MoveType::EnPassant);
                    validMoves.push_back(m);
                }
            }

        } else {
            if (board->getSquare(curX, curY + direction)->getPiece() == nullptr) {
                Move m = Move(square, board->getSquare(curX, curY + direction));
                if (curY + direction == 0) {
                    m.setMoveType(MoveType::Promotion);
                } else {
                    m.setMoveType(MoveType::Normal);
                }
                validMoves.push_back(m);
            }
            if (curY == 6 && board->getSquare(curX, curY + 2 * direction)->getPiece() == nullptr && board->getSquare(curX, curY + direction)->getPiece() == nullptr && !getHasMoved()){
                Move m = Move(square, board->getSquare(curX, curY + 2 * direction));
                m.setMoveType(MoveType::DoublePawn);
                validMoves.push_back(m);
            }
            if (curX - 1 >= 0 && board->getSquare(curX - 1, curY + direction)->getPiece() != nullptr && board->getSquare(curX - 1, curY + direction)->getPiece()->getColour() != colour) {
                Move m = Move(square, board->getSquare(curX - 1, curY + direction));
                m.setMoveType(MoveType::Capture);
                if (curY + direction == 0) {
                    m.setPawnSecondary(MoveType::Promotion);
                } 
                validMoves.push_back(m);
            }
            if (curX + 1 < 8 && board->getSquare(curX + 1, curY + direction)->getPiece() != nullptr && board->getSquare(curX + 1, curY + direction)->getPiece()->getColour() != colour) {
                Move m = Move(square, board->getSquare(curX + 1, curY + direction));
                m.setMoveType(MoveType::Capture);
                if (curY + direction == 0) {
                    m.setPawnSecondary(MoveType::Promotion);
                } 
                validMoves.push_back(m);
            }
            if (curY == 3) {
                if (curX - 1 >= 0 && board->getSquare(curX - 1, curY)->getPiece() != nullptr && board->getSquare(curX - 1, curY)->getPiece()->getPieceType() == PieceType::pawn && board->getSquare(curX - 1, curY)->getPiece()->getColour() != colour && board->getSquare(curX - 1, curY)->getPiece()->getEnPassantable()) {
                    Move m = Move(square, board->getSquare(curX - 1, curY + direction));
                    m.setMoveType(MoveType::EnPassant);
                    validMoves.push_back(m);
                }
                if (curX + 1 < 8 && board->getSquare(curX + 1, curY)->getPiece() != nullptr && board->getSquare(curX + 1, curY)->getPiece()->getPieceType() == PieceType::pawn && board->getSquare(curX + 1, curY)->getPiece()->getColour() != colour && board->getSquare(curX + 1, curY)->getPiece()->getEnPassantable()) {
                    Move m = Move(square, board->getSquare(curX + 1, curY + direction));
                    m.setMoveType(MoveType::EnPassant);
                    validMoves.push_back(m);
                }
        }
    }
    return validMoves;
    }
}
