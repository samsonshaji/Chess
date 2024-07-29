#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"
#include "board.h"

class Queen : public Piece {
public:
    Queen(Colour c);
    std::vector<Move> getAllMoves() const override;
};

#endif 
