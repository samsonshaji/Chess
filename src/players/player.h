#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"
#include "board.h"
#include "colour.h"
#include <string>

using namespace std;

class Player {
    protected:
        Colour colour;
    public:
        Player(Colour c);
        Colour getColour() const;
        virtual Move makeMove(Board &board, const string &to, const string &from, const string &promote) = 0;
        virtual ~Player();
        virtual bool isRobot() = 0;
};

#endif 