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

// Represents the chess board
class Board : public Subject, public std::enable_shared_from_this<Board> {
private:
    std::vector<std::vector<std::shared_ptr<Square>>> board;
    Controller* controller;
    //Stack of moves made in the game, used for undo functionality and validation
    std::vector<Move> moveStack;
public:
    Board();
    ~Board();
    //returns the square of the king of the given colour
    std::shared_ptr<Square> findKing(Colour colour) const;

    void setSquares();

    //initializes the board with the standard chess setup
    void setupInitialBoard();
    //move a piece from one square to another
    bool movePiece(const Move& move);
    //move a piece from one square to another, without checking if the move is legal
    //this is used for validation purposes
    bool overrideMovePiece(const Move& move);
    //check if the given colour's king is in check
    bool isInCheck(Colour colour) const;
    //check if the given colour's king is in checkmate
    bool isCheckmate(Colour colour);
    //check if the game is in stalemate
    bool isStalemate(Colour colour) const;
    //check if the Move will break any rules
    bool isMoveLegal(const Move& move);
    //given a move, determine the type of move
    MoveType determineMoveType(const Move& move);
    //undo a move
    void undoMove();
    // add a piece to the board at the given square
    void addPiece(std::shared_ptr<Piece> piece, std::shared_ptr<Square> square);
    // remove a piece from the board
    void removePiece(std::shared_ptr<Square> square);
    //wipe the pieces from the board
    void clearBoard();

    //check if the custom board setup is valid
    bool isValidSetup() const;

    //getters and setters
    void setController(Controller* ctrl);
    std::shared_ptr<Square> getSquare(int x, int y) const;

    std::vector<Move> getMoveStack() const;
    Move getLastMove() const;
    std::vector<std::vector<std::shared_ptr<Square>>> getState() const override;
};

#endif 
