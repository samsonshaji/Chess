#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
private:
    void addDiagonalMoves(std::vector<Move>& moves, int xDir, int yDir) const;
public:
    Bishop(Colour c);
    std::vector<Move> getValidMoves() const override;

};

#endif 
