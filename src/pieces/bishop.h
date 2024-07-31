#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
private:
public:
    Bishop(Colour c);
    ~Bishop();
    //all possible moves a bishop can make
    std::vector<Move> getValidMoves() const override;
};

#endif 
