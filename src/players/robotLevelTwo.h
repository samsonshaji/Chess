#ifndef ROBOT_LEVEL_TWO_H
#define ROBOT_LEVEL_TWO_H

#include "robot.h"

class LevelTwo : public Robot {
    private:
        void generateMoves() override;
    public:
        LevelTwo(Colour c, Board *b);
        ~LevelTwo();
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif