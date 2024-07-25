#ifndef ROBOT_LEVEL_FOUR_H
#define ROBOT_LEVEL_FOUR_H

#include "robot.h"

class LevelFour : public Robot {
    public:
        LevelFour();
        virtual Move makeMove(const Board& board) override;
};

#endif