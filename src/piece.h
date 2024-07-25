#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece {
public:
    Piece(bool isWhite);
    virtual ~Piece() = default;
    virtual bool isMoveValid(int startX, int startY, int endX, int endY) const = 0;
    bool isWhite() const;
    virtual std::string getSymbol() const = 0;
private:
    bool white;
};

#endif // PIECE_H
