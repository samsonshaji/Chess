#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "move.h"
#include "board.h"
#include "piecetype.h"

class Rook : public Piece {
private:
    void addStraightMoves(std::vector<Move>& moves, int xDir, int yDir) const;
public:
    Rook(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif