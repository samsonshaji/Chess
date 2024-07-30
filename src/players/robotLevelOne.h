#ifndef ROBOT_LEVEL_ONE_H
#define ROBOT_LEVEL_ONE_H

#include "robot.h"

class LevelOne : public Robot {
    public:
        LevelOne(Colour c, Board *b);
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif