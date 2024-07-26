#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    PieceType getType() const override;
    std::vector<Move> getMoveStack() const override;
    bool isMoveValid(const Move &m, const Board &board) const override;
    int getPoints() const override;
    PieceType getPieceType() const override;
    bool isPinned(const Board &b) const override;
    bool canCheck(const Board &b) const override;
    void move(const Move &m) override;
};

#endif 
