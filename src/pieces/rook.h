#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "move.h"
#include "board.h"
#include "piecetype.h"

class Rook : public Piece {
private:
public:
    Rook(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif