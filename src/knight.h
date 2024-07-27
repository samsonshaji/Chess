#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include <vector>

class Knight : public Piece {
public:
    Knight(Colour c);
    PieceType getPieceType() const override;
    std::vector<Move> getValidMoves() const override;
};

#endif 
