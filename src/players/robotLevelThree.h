#ifndef ROBOT_LEVEL_THREE_H
#define ROBOT_LEVEL_THREE_H

#include "robot.h"

class LevelThree : public Robot {
    public:
        LevelThree();
        virtual Move makeMove(const Board& board) override;
};

#endif