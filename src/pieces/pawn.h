#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
private:
    //helper function for en passant behaviour
    bool isEnPassantValid(const Board &b, int side) const;

public:
    Pawn(Colour c);
    ~Pawn();
    //all possible pawn behaviour
    std::vector<Move> getValidMoves() const override;
};

#endif 
