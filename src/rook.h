#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook(Colour c);
    std::vector<Move> getValidMoves() const override;
};
