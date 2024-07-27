#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(Colour c);
    PieceType getPieceType() const override;
    std::vector<Move> getValidMoves() const override;
    bool isEnPassantValid(const Board &b, int side) const;

    // bool isPinned(const Board &b) const override;
    // bool canCheck(const Board &b) const override;
    // void move(const Move &m) override;
    // bool isPromoteValid(const Board &b) const;
    // bool isCaptureValid(const Board &b) const;
    // bool canDoubleMove(const Board &b) const;
};

#endif 
