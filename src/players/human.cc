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
        return Move(nullptr, nullptr);
    }

    int fy = from[1] - '1';
    int fx = from[0] - 'a';
    int ty = to[1] - '1';
    int tx = to[0] - 'a';

    Square *fromSquare = board.getSquare(fx, fy);
    Square *toSquare = board.getSquare(tx, ty);

    if (fromSquare->getPiece() == nullptr) {
        return Move(nullptr, nullptr);
    }

    if (promote != "") {
        return Move(fromSquare, toSquare, Promotion, promote[0]);
    }
    
    return Move(fromSquare, toSquare);
}