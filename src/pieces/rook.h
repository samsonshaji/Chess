#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "move.h"
#include "board.h"
#include "piecetype.h"

class Rook : public Piece {
public:
    Rook(Colour c);
    std::vector<Move> getAllMoves() const override;
};

#endif