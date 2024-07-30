#ifndef ROBOT_LEVEL_THREE_H
#define ROBOT_LEVEL_THREE_H

#include "robot.h"

class LevelThree : public Robot {
    public:
        LevelThree(Colour c, Board *b);
        ~LevelThree();
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif