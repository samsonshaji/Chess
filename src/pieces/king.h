#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Colour c);
    std::vector<Move> getAllMoves() const override;
};

#endif
