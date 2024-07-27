#ifndef ROBOT_LEVEL_ONE_H
#define ROBOT_LEVEL_ONE_H

#include "robot.h"


class LevelOne : public Robot {
    public:
        LevelOne();
        virtual Move makeMove(const Board& board) override;
};

#endif