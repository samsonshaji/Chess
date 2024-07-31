#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

class Square {
private:
    //coordinates of the square in the board logic ((0,0) to (7,7))
    int x;
    int y;
    //pointer to the piece on the square
    Piece* piece=nullptr;
    Board* board;

public:

    //square only ever gets made once and stays at the same location
    Square(int x, int y);
    //destructor
    ~Square();
    //deletes the piece on the square
    void deletePiece();

    //getters and setters
    Piece* getPiece() const;
    void setPiece(Piece* p);
    void setBoard(Board* b);
    int getX() const;
    int getY() const;
};

#endif // SQUARE_H
