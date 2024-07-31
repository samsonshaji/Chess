#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "movetype.h"

using namespace std;

class Human : public Player {
private:
    //initial input checking
    bool validMoveCmd(const string &from, const string &to, const string &promote);
public:
    //constructor, build a human player with a specific colour
    Human(Colour colour);
    //human input
    virtual Move makeMove(Board &board, const string &from, const string &to, const string &promote) override;
    //returns false
    virtual bool isRobot() override;
    ~Human();
};

#endif 