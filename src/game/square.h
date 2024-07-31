#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"
#include <memory>

class Square : public std::enable_shared_from_this<Square> {
private:
    int x;
    int y;
    std::shared_ptr<Piece> piece=nullptr;
    std::shared_ptr<Board> board;

public:

    Square(int x, int y);
    ~Square();

    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> p);
    void setBoard(std::shared_ptr<Board> b);
    void removePiece();
    void deletePiece();
    int getX() const;
    int getY() const;
};

#endif // SQUARE_H
