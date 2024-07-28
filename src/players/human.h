#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "movetype.h"

class Human : public Player {
private:
    bool validMoveCmd(const string &from, const string &to, const string &promote);
public:
    Human(Colour colour);
    virtual Move makeMove(const Board &board, const string &from, const string &to, const string &promote) override;
};

#endif 