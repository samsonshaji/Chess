#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "subject.h"
#include "move.h"
#include "square.h"
#include "colour.h"
#include "controller.h"
#include "piece.h"

class Controller;

class Board : public Subject, public std::enable_shared_from_this<Board> {
private:
    std::vector<std::vector<std::shared_ptr<Square>>> board;
    Controller* controller;
    std::vector<Move> moveStack;
public:
    Board();
    ~Board();
    std::shared_ptr<Square> findKing(Colour colour) const;

    void setSquares();

    void setupInitialBoard();

    void setController(Controller* ctrl);
    std::shared_ptr<Square> getSquare(int x, int y) const;

    std::vector<Move> getMoveStack() const;
    Move getLastMove() const;

    void addMoveToStack(const Move& move);
    void undoMove();

    void addPiece(std::shared_ptr<Piece> piece, std::shared_ptr<Square> square);
    void removePiece(std::shared_ptr<Square> square);
    void clearBoard();

    bool isValidSetup() const;

    std::vector<std::vector<std::shared_ptr<Square>>> getState() const override;

    bool movePiece(const Move& move);
    bool overrideMovePiece(const Move& move);
    

    bool isInCheck(Colour colour) const;
    bool isCheckmate(Colour colour);
    bool isStalemate(Colour colour) const;

    void print() const;

    bool isMoveLegal(const Move& move);
    std::vector<std::vector<std::shared_ptr<Square>>> getBoard();

    MoveType determineMoveType(const Move& move);
};

#endif 
