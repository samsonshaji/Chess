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

bool Pawn::isEnPassantValid(const Board &board, int side) const {
    int curX = square->getX();
    int curY = square->getY();
    int direction = (colour == Colour::White) ? 1 : -1;

    if (curX + side < 0 || curX + side >= 8 || curY + direction < 0 || curY + direction >= 8) {
        return false;
    }

    Square* adjacentSquare = board.getSquare(curX + side, curY);
    Square* targetSquare = board.getSquare(curX + side, curY + direction);

    if (adjacentSquare->getPiece() &&
        adjacentSquare->getPiece()->getPieceType() == PieceType::pawn &&
        adjacentSquare->getPiece()->getColour() != colour &&
        targetSquare->getPiece() == nullptr) {

        // Check if the adjacent pawn moved two squares in the previous movex
        Move lastMove = board.getLastMove();
        if (lastMove.getTo()->getPiece()->getPieceType() == PieceType::pawn &&
            lastMove.getTo() == adjacentSquare &&
            abs(lastMove.getFrom()->getY() - lastMove.getTo()->getY()) == 2) {
            return true;
        }
    }

    return false;
}

std::vector<Move> Pawn::getValidMoves() const {
    std::vector<Move> validMoves;

    if (!square || !board) return validMoves;

    int curX = square->getY();
    int curY = square->getX();
    int direction = (colour == Colour::White) ? 1 : -1;

    // Single move forward
    if (curY + direction >= 0 && curY + direction < 8) {
        // std::cout << "FHWY WONT IT OWRK" << std::endl;
        // std::cout << "curX: " << curX << " curY: " << curY << " direction: " << direction << std::endl;
        Square* forwardSquare = board->getSquare(curX, curY + direction);
        if (forwardSquare->getPiece() == nullptr) {
            validMoves.push_back(Move(square, forwardSquare, MoveType::Normal));

            // Double move forward
            if (!hasMoved && curY + 2 * direction >= 0 && curY + 2 * direction < 8) {
                Square* doubleForwardSquare = board->getSquare(curX, curY + 2 * direction);
                if (doubleForwardSquare->getPiece() == nullptr) {
                    validMoves.push_back(Move(square, doubleForwardSquare, MoveType::DoublePawn));
                }
            }
        }
    }

    // Captures and En Passant
    for (int side : {-1, 1}) {
        if (curX + side >= 0 && curX + side < 8 && curY + direction >= 0 && curY + direction < 8) {
            Square* captureSquare = board->getSquare(curX + side, curY + direction);
            if (captureSquare->getPiece() && captureSquare->getPiece()->getColour() != colour) {
                if (captureSquare->getPiece()->getPieceType() == PieceType::king) {
                    board->isInCheck(captureSquare->getPiece()->getColour());
                }
                validMoves.push_back(Move(square, captureSquare, MoveType::Capture));
            }
            if (isEnPassantValid(*board, side)) {
                Square* enPassantSquare = board->getSquare(curX + side, curY + direction);
                validMoves.push_back(Move(square, enPassantSquare, MoveType::EnPassant));
            }
        }
    }

    return validMoves;
}
