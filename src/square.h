#ifndef SQUARE_H
#define SQUARE_H


// square is a subject in the observer pattern
#include <iostream>
#include <iomanip>
#include <string>

#include "observer.h"
#include "piece.h"

enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King, Empty };
enum class Color { White, Black };

class Square {
    private:
        PieceType piece;
        Color color;
        Move move;
        std::vector<Observer *> observers;
    public:
        Square();
        Square(PieceType p, Color c);
        PieceType getPiece() const;
        Color getColor() const;
        void setPiece(PieceType p);
        void setColor(Color c);

        void attach(Observer *o);
        void detach(Observer *o);
        void notifyObservers();
        void setSquare(Piece *newPiece, Color newColor);

        friend std::ostream &operator<<(std::ostream &out, const Square &s);
};

#endif
