#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Colour c);
    PieceType getPieceType() const override;
    bool isKingMoveValid(const Move& move, const Board& board) const;
    std::vector<Move> getValidMoves() const override;
    bool canCastle(const Board& b) const;
};

#endif
