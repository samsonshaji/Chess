#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"
#include <memory>

class Square : public std::enable_shared_from_this<Square> {
private:
    //coordinates of the square in the board logic ((0,0) to (7,7))
    int x;
    int y;

    //pointer to the piece on the square
    std::shared_ptr<Piece> piece=nullptr;
    std::shared_ptr<Board> board;

public:

    //square only ever gets made once and stays at the same location
    Square(int x, int y);
    //destructor
    ~Square();
    //deletes the piece on the square
    void deletePiece();

    // getters and setters
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> p);
    void setBoard(std::shared_ptr<Board> b);
    int getX() const;
    int getY() const;
};

#endif // SQUARE_H
