#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
private:
public:
    King(Colour c);
    ~King();
    std::vector<Move> getValidMoves() const override;
};

#endif
