#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include <vector>

class Knight : public Piece {
public:
    Knight(Colour c);
    ~Knight();
    //all possible knight behaviour
    std::vector<Move> getValidMoves() const override;
};

#endif 
