#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
private:
    bool isKingMoveValid(const Move& move, const Board& board) const;
public:
    King(Colour c);
    std::vector<Move> getValidMoves() const override;
};

#endif
