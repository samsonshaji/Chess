#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <iostream>
#include "moveException.h"

enum class MoveType { Normal, EnPassant, Castling, Promotion };

class Move {
    private:
        int oldRow;
        int oldCol;
        int newRow;
        int newCol;
    public:
        Move(int oldRow, int oldCol, int newRow, int newCol);
        int getOldRow() const;
        int getOldCol() const;
        int getNewRow() const;
        int getNewCol() const;
        std::string toString() const;
        bool operator==(const Move &m) const;
        bool operator!=(const Move &m) const;
        friend std::ostream& operator<<(std::ostream &out, const Move &m);
        MoveType getMoveType() const;
        void executeMove();
        void undoMove();
};

#endif