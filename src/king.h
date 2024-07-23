#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    bool isMoveValid(Move m, const Board &b) const override;
    PieceType getType() const override { return PieceType::King; }
    std::string toString() const override;
    std::string toGraphics() const override;
    Piece* clone() const override;
    bool hasMoved() const override { return moved; }
    void setMoved() override { moved = true; }
    void move(Move m, Board &b) override;
    bool isAttackingSquare(Move m, const Board &b) const override;
    bool isPinned(const Board &b) const override;
    bool isCheckingSquare(Move m, const Board &b) const override;
    int getPoints() const override { return 0; }
    bool canCheck(const Board &b) const override;
private:
    bool moved = false;
};

#endif