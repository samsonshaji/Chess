#include "human.h"

Human::Human(Colour colour) : Player(colour) {}

Move Human::makeMove(const Board &board) {
    int oldRow, oldCol, newRow, newCol;
    std::cout << "Enter your move (oldRow oldCol newRow newCol): ";
    std::cin >> oldRow >> oldCol >> newRow >> newCol;

    Square *from = nullptr;
    Square *to = nullptr;

    // find square in board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getSquare(i, j)->getX() == oldRow && board.getSquare(i, j)->getY() == oldCol) {
                from = board.getSquare(i, j);
            }
            if (board.getSquare(i, j)->getX() == newRow && board.getSquare(i, j)->getY() == newCol) {
                to = board.getSquare(i, j);
            }
        }
    }

    Move move(from, to);
    return move;
}

