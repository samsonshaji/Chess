#include "human.h"
#include <iostream>
#include <string>

Human::Human(Colour colour) : Player(colour) {}

bool Human::validMoveCmd(const string &from, const string &to, const string &promote) {
    if (to.length() != 2 || from.length() != 2) {
        return false;
    }

    if (to[0] < 'a' || to[0] > 'h' || to[1] < '1' || to[1] > '8') {
        return false;
    }

    if (from[0] < 'a' || from[0] > 'h' || from[1] < '1' || from[1] > '8') {
        return false;
    }

    if (promote.length() > 1) {
        return false;
    }

    if (promote.length() == 1 && (promote != "Q" && promote != "q" && promote != "R" && promote != "r" && promote != "B" && promote != "b" && promote != "N" && promote != "n")) {
        return false;
    }

    return true;
}

Move Human::makeMove(const Board &board, const string &from, const string &to, const string &promote) {
    if (!validMoveCmd(from, to, promote)) {
        return Move(nullptr, nullptr, Invalid);
    }

    int frow = '8' - from[1];
    int fcol = from[0] - 'a';
    int trow = '8' - to[1];
    int tcol = to[0] - 'a';

    Square *fromSquare = board.getSquare(frow, fcol);
    Square *toSquare = board.getSquare(trow, tcol);

    if (fromSquare->getPiece() == nullptr) {
        return Move(nullptr, nullptr, Invalid);
    }

    if (promote != "") {
        return Move(fromSquare, toSquare, Promotion, promote[0]);
    }
    
    return Move(fromSquare, toSquare);
}

