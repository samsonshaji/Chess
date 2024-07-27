#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "piece.h"
#include "move.h"
#include "board.h"

class Rook : public Piece {
public:
    Rook(Colour c);
    std::vector<Move> getValidMoves() const override;
    bool canCastle() const;
};

#endif