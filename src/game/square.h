#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

class Square {
private:
    int x;
    int y;
    Piece* piece=nullptr;
    Board* board;

public:

    Square(int x, int y);

    Piece* getPiece() const;
    void setPiece(Piece* p);
    void setBoard(Board* b);
    void removePiece();
    void deletePiece();
    int getX() const;
    int getY() const;
};

#endif // SQUARE_H
