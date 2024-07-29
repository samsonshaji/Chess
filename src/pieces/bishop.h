#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
private:
public:
    Bishop(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif 
