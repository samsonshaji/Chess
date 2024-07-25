#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

class Square {
public:
    int x;
    int y;
    Piece* piece;

    Square(int x, int y);
    Square();

    bool isValid() const;
    Piece* getPiece() const;
    void setPiece(Piece* piece);
};

#endif // SQUARE_H
