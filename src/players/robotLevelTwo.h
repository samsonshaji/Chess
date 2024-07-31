#ifndef ROBOT_LEVEL_TWO_H
#define ROBOT_LEVEL_TWO_H

#include "robot.h"

class LevelTwo : public Robot {
    public:
        LevelTwo(Colour c, std::shared_ptr<Board>b);
        ~LevelTwo();
        // Make a valid move, as per robot level
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif