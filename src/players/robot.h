#ifndef ROBOT_H
#define ROBOT_H
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <vector>

class Robot : public Player {
protected:
    std::shared_ptr<Board>board;
public:
    Robot(Colour c, std::shared_ptr<Board>b);
    virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) = 0;
    virtual ~Robot() = 0;
    virtual bool isRobot() override;
};

#endif