#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
private:
    bool isEnPassantValid(const Board &b, int side) const;

public:
    Pawn(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif 
