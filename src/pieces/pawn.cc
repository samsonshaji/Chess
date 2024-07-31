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

Pawn::~Pawn() {}

bool Pawn::isEnPassantValid(const Board &board, int side) const {
    int curX = square->getX();
    int curY = square->getY();
    int direction = (colour == Colour::White) ? 1 : -1;

    if (curX + side < 0 || curX + side >= 8 || curY + direction < 0 || curY + direction >= 8) {
        return false;
    }

    std::shared_ptr<Square> adjacentSquare = board.getSquare(curX + side, curY);
    std::shared_ptr<Square> targetSquare = board.getSquare(curX + side, curY + direction);

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

    int curX = square->getX();
    int curY = square->getY();
    int direction = (colour == Colour::White) ? 1 : -1;

    // single move forward
    if (board->getSquare(curX, curY + direction)->getPiece() == nullptr) {
        MoveType moveType = MoveType::Normal;
        if (curY + direction == 0 || curY + direction == 7) {
            moveType = MoveType::Promotion;
        }
        validMoves.push_back(Move(square, board->getSquare(curX, curY + direction), moveType));
    }

    // double move forward
    if ((colour == Colour::White && curY == 1) || (colour == Colour::Black && curY == 6)) {
        if (board->getSquare(curX, curY + direction)->getPiece() == nullptr &&
            board->getSquare(curX, curY + 2 * direction)->getPiece() == nullptr) {
            validMoves.push_back(Move(square, board->getSquare(curX, curY + 2 * direction), MoveType::DoublePawn));
        }
    }

    // capture
    for (int i = -1; i <= 1; i += 2) {
        if (curX + i < 0 || curX + i >= 8) continue;
        std::shared_ptr<Square> targetSquare = board->getSquare(curX + i, curY + direction);
        if (targetSquare && targetSquare->getPiece() && targetSquare->getPiece()->getColour() != colour) {
            MoveType moveType = MoveType::Normal;
            if (curY + direction == 0 || curY + direction == 7) {
                moveType = MoveType::Promotion;
            }
            validMoves.push_back(Move(square, targetSquare, moveType));
        }
    }

    // en passant
    for (int i = -1; i <= 1; i += 2) {
        if (isEnPassantValid(*board, i)) {
            validMoves.push_back(Move(square, board->getSquare(curX + i, curY + direction), MoveType::EnPassant));
        }
    }

    return validMoves;
}
