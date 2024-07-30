#ifndef ROBOT_LEVEL_FOUR_H
#define ROBOT_LEVEL_FOUR_H

#include "robot.h"

class LevelFour : public Robot {
    int getPoints(PieceType pt);
public:
    LevelFour(Colour c, Board *b);
    ~LevelFour();
    virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif