#ifndef ROBOT_LEVEL_FOUR_H
#define ROBOT_LEVEL_FOUR_H

#include "robot.h"

class LevelFour : public Robot {
    // Points for each piece type
    int getPoints(PieceType pt);
public:
    LevelFour(Colour c, std::shared_ptr<Board>b);
    ~LevelFour();
    // Make a move, as per robot level
    virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) override;
};

#endif