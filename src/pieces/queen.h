#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"
#include "board.h"

class Queen : public Piece {
private:
    void addDiagonalMoves(std::vector<Move>& moves, int xDir, int yDir) const;
    void addStraightMoves(std::vector<Move>& moves, int xDir, int yDir) const;
public:
    Queen(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif 
