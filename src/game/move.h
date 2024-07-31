#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <vector>
#include <string>

#include "square.h"
#include "movetype.h"

//object for any move made
class Move {
    private:
        //square the move started at
        Square* from;
        //square the move ended at
        Square* to;
        //type of move
        MoveType type;
        //promote to this type if move is a promotion
        char promotedTo;
        //piece that was captured in a move
        Piece *capturedPiece=nullptr;
        //pawn that was promoted in a move
        Piece *promotedPawn=nullptr;

    public:
        //Default constructor
        Move();
        ~Move();
        //Custom constructors
        Move(Square* f, Square* t);
        Move(Square* f, Square* t, MoveType mt);
        Move(Square* f, Square* t, MoveType mt, char p);
        
        //Copy constructor and assignment operator
        Move(const Move& m);
        Move& operator=(const Move& m);

        //overload the equality operator to compare Moves
        bool operator==(const Move& m) const;

        //getters and setters
        MoveType getMoveType() const;
        void setMoveType(MoveType t);

        Square* getFrom() const;
        Square* getTo() const;

        char getPromotedTo() const;
        void setPromotedTo(char p);

        Piece* getCapturedPiece() const;
        void setCapturedPiece(Piece* piece);

        Piece* getPromotedPawn();
        void setPromotedPawn(Piece* piece);
};

#endif