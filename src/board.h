#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "scoreBoard.h"
#include "observer.h"
#include "square.h"
#include "move.h"

enum class Color { White, Black };
enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King, Empty };

class Board: public Observer {
    private:
        std::vector<std::vector<Square>> board;
        ScoreBoard scoreBoard;
    public:
        Board();
        void notify() override;
        void move(Move m);
        void isCheck(Color c);
        void isCheckmate(Color c);
        void isStalemate(Color c);
        PieceType getPieceType(int row, int col) const;
};

#endif