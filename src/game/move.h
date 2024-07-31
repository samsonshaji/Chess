#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <vector>
#include <string>

#include "square.h"
#include "movetype.h"

class Move {
    private:
        std::shared_ptr<Square> from;
        std::shared_ptr<Square> to;
        MoveType type;
        char promotedTo;
        std::shared_ptr<Piece>capturedPiece=nullptr;
        std::shared_ptr<Piece>promotedPawn=nullptr;

    public:
        Move();
        ~Move();
        Move(std::shared_ptr<Square> f, std::shared_ptr<Square> t);
        Move(std::shared_ptr<Square> f, std::shared_ptr<Square> t, MoveType mt);
        Move(std::shared_ptr<Square> f, std::shared_ptr<Square> t, MoveType mt, char p);
        
        Move(const Move& m);
        Move& operator=(const Move& m);

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

        bool operator==(const Move& m) const;

};

#endif