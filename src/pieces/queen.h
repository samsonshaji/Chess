#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "move.h"
#include "board.h"

class Queen : public Piece {
private:
public:
    Queen(Colour c);
    ~Queen();
    std::vector<Move> getValidMoves() const override;
};

#endif 
