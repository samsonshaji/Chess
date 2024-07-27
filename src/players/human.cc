#include "human.h"

Human::Human(Colour colour) : Player(colour) {}

Colour Human::getColour() const {
    return colour;
}

Move Human::makeMove(const Board &board) {
    int oldRow, oldCol, newRow, newCol;
    std::cout << "Enter your move (oldRow oldCol newRow newCol): ";
    std::cin >> oldRow >> oldCol >> newRow >> newCol;
    Square from = Square(oldRow, oldCol);
    Square to = Square(newRow, newCol);
    Move move = Move(from, to);
    return move;
}

