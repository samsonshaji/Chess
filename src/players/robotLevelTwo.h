#ifndef ROBOT_LEVEL_TWO_H
#define ROBOT_LEVEL_TWO_H

#include "robot.h"

class LevelTwo : public Robot {
    public:
        LevelTwo();
        virtual Move makeMove(const Board& board) override;
};

#endif