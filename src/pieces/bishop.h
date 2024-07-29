#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(Colour c);
    std::vector<Move> getAllMoves() const override;

};

#endif 
