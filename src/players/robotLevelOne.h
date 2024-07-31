#ifndef ROBOT_LEVEL_ONE_H
#define ROBOT_LEVEL_ONE_H

#include "robot.h"

class LevelOne : public Robot {
    public:
        LevelOne(Colour c, std::shared_ptr<Board>b);
        ~LevelOne();
        // Make a move, as per robot level
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif