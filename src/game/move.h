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
        std::shared_ptr<Square> from;
        //square the move ended at
        std::shared_ptr<Square> to;
        //type of move
        MoveType type;
        //promote to this type if move is a promotion
        char promotedTo;
        //piece that was captured in a move
        std::shared_ptr<Piece>capturedPiece=nullptr;
        //pawn that was promoted in a move
        std::shared_ptr<Piece>promotedPawn=nullptr;

    public:
        //Default constructor
        Move();
        ~Move();
        //Custom constructors
        Move(std::shared_ptr<Square> f, std::shared_ptr<Square> t);
        Move(std::shared_ptr<Square> f, std::shared_ptr<Square> t, MoveType mt);
        Move(std::shared_ptr<Square> f, std::shared_ptr<Square> t, MoveType mt, char p);
        
        //Copy constructor and assignment operator
        Move(const Move& m);
        Move& operator=(const Move& m);

        //overload the equality operator to compare Moves
        bool operator==(const Move& m) const;

        //getters and setters
        MoveType getMoveType() const;
        void setMoveType(MoveType t);

        std::shared_ptr<Square> getFrom() const;
        std::shared_ptr<Square> getTo() const;

        char getPromotedTo() const;
        void setPromotedTo(char p);

        std::shared_ptr<Piece> getCapturedPiece() const;
        void setCapturedPiece(std::shared_ptr<Piece> piece);

        std::shared_ptr<Piece> getPromotedPawn();
        void setPromotedPawn(std::shared_ptr<Piece> piece);
};

#endif