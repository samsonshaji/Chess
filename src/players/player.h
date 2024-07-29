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
        Player(Colour c): colour{c} {}
        Colour getColour() const { return colour; }
        virtual Move makeMove(const Board &board, const string &to, const string &from, const string &promote) = 0;
        virtual ~Player();
};

#endif 