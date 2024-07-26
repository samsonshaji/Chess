#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"
#include "board.h"
#include <vector>

class Queen : public Piece {
public:
    Queen(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif 
