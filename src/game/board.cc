#include "board.h"
#include <iostream>
#include <algorithm>
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "colour.h"
#include "move.h"
#include "square.h"

//construct a board with 8x8 squares when the program is first run
Board::Board() {
    for (int i = 0; i < 8; i++) {
        std::vector<Square*> row;
        for (int j = 0; j < 8; j++) {
            Square* s = new Square(j, i);
            s->setBoard(this);
            row.push_back(s);
        }
        board.push_back(row);
    }
    //initialize the board with the standard chess setup
    setupInitialBoard();
}

Board::~Board() {
    for (auto& row : board) {
        for (auto& square : row) {
            //delete all squares
            delete square;
            square = nullptr;
        }
    }
    controller = nullptr;
}

void Board::clearBoard() {
    for (auto& row : board) {
        for (auto& square : row) {
            if (square->getPiece() != nullptr) {
                //delete piece at every square
                delete square->getPiece();
            }
            square->setPiece(nullptr);
        }
    }
    //delete any pieces that aren't on the board
    //may have been captured or promoted
    for (auto move : moveStack) {
        if (move.getCapturedPiece() != nullptr) {
            delete move.getCapturedPiece();
            move.setCapturedPiece(nullptr);
        }
        else if( move.getPromotedPawn() != nullptr){
            delete move.getPromotedPawn();
            move.setPromotedPawn(nullptr);
        }
    }
    moveStack.clear();
}

void Board::setupInitialBoard() {
    // white pieces
    board[0][0]->setPiece(new Rook(Colour::White));
    board[0][1]->setPiece(new Knight(Colour::White));
    board[0][2]->setPiece(new Bishop(Colour::White));
    board[0][3]->setPiece(new Queen(Colour::White));
    board[0][4]->setPiece(new King(Colour::White));
    board[0][5]->setPiece(new Bishop(Colour::White));
    board[0][6]->setPiece(new Knight(Colour::White));
    board[0][7]->setPiece(new Rook(Colour::White));
    for (int i = 0; i < 8; i++) {
        board[1][i]->setPiece(new Pawn(Colour::White));
    }

    // black pieces
    board[7][0]->setPiece(new Rook(Colour::Black));
    board[7][1]->setPiece(new Knight(Colour::Black));
    board[7][2]->setPiece(new Bishop(Colour::Black));
    board[7][3]->setPiece(new Queen(Colour::Black));
    board[7][4]->setPiece(new King(Colour::Black));
    board[7][5]->setPiece(new Bishop(Colour::Black));
    board[7][6]->setPiece(new Knight(Colour::Black));
    board[7][7]->setPiece(new Rook(Colour::Black));
    for (int i = 0; i < 8; i++) {
        board[6][i]->setPiece(new Pawn(Colour::Black));
    }
}

void Board::addPiece(Piece* piece, Square* square) {
    square->setPiece(piece);
}

void Board::removePiece(Square* square) {
   if (square->getPiece() != nullptr) {
        //delete piece at square
        delete square->getPiece();
    }
    square->setPiece(nullptr);}

std::vector<std::vector<Square*>> Board::getState() const {
    return board;
}

Square* Board::getSquare(int x, int y) const {
    //check if the coordinates are within the board
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return nullptr;
    }
    //return the square at the given coordinates
    //flipped because of 2D vector is setup
    return board[y][x];
}

void Board::setController(Controller* ctrl) {
    controller = ctrl;
}

Square* Board::findKing(Colour colour) const {
    //iterate through the entire board
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();

            if (piece == nullptr) {
            }
            //given color is the same as the piece's color and the piece is a king
            if (piece && piece->getColour() == colour && piece->getPieceType() == PieceType::king) {
                return square;
            }
        }
    }
    // not found -- should never happen
    return nullptr;
}

std::vector<Move> Board::getMoveStack() const {
    return moveStack;
}

Move Board::getLastMove() const {
    return moveStack.back();
}

bool Board::isMoveLegal(const Move& move) {
    //check that the square where the move starts exists
    if (move.getFrom() == nullptr) {
        return false;
    }
    //check that there is a piece at the square where the move starts
    if (move.getFrom()->getPiece() == nullptr) {
        return false;
    }

    Colour colour = move.getFrom()->getPiece()->getColour();

    // find all valid moves of all pieces of the given colour
    std::vector<Move> validMoves;

    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> temp = piece->getValidMoves();
                validMoves.insert(validMoves.end(), temp.begin(), temp.end());
            }
        }
    }

    // check if the move is in the list of valid moves
    if (std::find(validMoves.begin(), validMoves.end(), move) == validMoves.end()) {
        return false;
    }

    // check if the move puts the king in check
    //simulate the move ahead of the play
    bool valid = overrideMovePiece(move);

    Square* whiteKing = findKing(Colour::White);
    Square* blackKing = findKing(Colour::Black);
    
    int whiteKingX = whiteKing->getX();
    int whiteKingY = whiteKing->getY();

    int blackKingX = blackKing->getX();
    int blackKingY = blackKing->getY();

    // check if the kings are within range of each other
    bool kingsTogether = false;
    if (whiteKingX-1 == blackKingX && whiteKingY-1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX-1 == blackKingX && whiteKingY == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX-1 == blackKingX && whiteKingY+1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX == blackKingX && whiteKingY-1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX == blackKingX && whiteKingY+1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX+1 == blackKingX && whiteKingY-1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX+1 == blackKingX && whiteKingY == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX+1 == blackKingX && whiteKingY+1 == blackKingY) {
        kingsTogether = true;
    }

    //kings should not be in range of each other
    if (kingsTogether) {
        undoMove();
        return false;
    }
    //check if the king is in check
    bool isCheck = isInCheck(colour);

    //if move is valid and the players king does not end up in check, return true
    if (valid) {
        undoMove();
        if (isCheck) {
            return false;
        }
    }
    return true;
}




bool Board::isValidSetup() const {
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece) {
                if (piece->getPieceType() == PieceType::king) {
                    if (piece->getColour() == Colour::White) {
                        whiteKingCount++;
                    } else {
                        blackKingCount++;
                    }
                }
            }
        }
    }
    //check that there is only one king of each color
    if (whiteKingCount != 1 || blackKingCount != 1) {
        return false;
    }

    // check if there are no pawns on the first or last row
    for (int i = 0; i < 8; i++) {
        if (board[0][i]->getPiece() && board[0][i]->getPiece()->getPieceType() == PieceType::pawn) {
            return false;
        }
        if (board[7][i]->getPiece() && board[7][i]->getPiece()->getPieceType() == PieceType::pawn) {
            return false;
        }
    }

    // check if there are no more than 8 pawns of each color
    int whitePawnCount = 0;
    int blackPawnCount = 0;
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getPieceType() == PieceType::pawn) {
                if (piece->getColour() == Colour::White) {
                    whitePawnCount++;
                } else {
                    blackPawnCount++;
                }
            }
        }
    }

    if (whitePawnCount > 8 || blackPawnCount > 8) {
        return false;
    }

    Square* whiteKing = findKing(Colour::White);
    Square* blackKing = findKing(Colour::Black);
    
    int whiteKingX = whiteKing->getX();
    int whiteKingY = whiteKing->getY();

    int blackKingX = blackKing->getX();
    int blackKingY = blackKing->getY();

    bool kingsTogether = false;
    if (whiteKingX-1 == blackKingX && whiteKingY-1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX-1 == blackKingX && whiteKingY == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX-1 == blackKingX && whiteKingY+1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX == blackKingX && whiteKingY-1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX == blackKingX && whiteKingY+1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX+1 == blackKingX && whiteKingY-1 == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX+1 == blackKingX && whiteKingY == blackKingY) {
        kingsTogether = true;
    } else if (whiteKingX+1 == blackKingX && whiteKingY+1 == blackKingY) {
        kingsTogether = true;
    }

    // ensure kings are not in range of each other
    if (kingsTogether) {
        return false;
    }

    // ensure neither king is in check
    if (isInCheck(Colour::White) || isInCheck(Colour::Black)) {
        return false;
    }

    return true;
}

bool Board::overrideMovePiece(const Move& move) {
    // check that the square where the move starts exists
    if (move.getFrom() == nullptr) {
        return false;
    }

    // check that there is a piece at the square where the move starts
    if (move.getFrom()->getPiece() == nullptr) {
        return false;
    }

    Square* from = move.getFrom();
    Square* to = move.getTo();
    Piece* piece = from->getPiece();
    piece->setBoard(this);

    Piece *capturedPiece = nullptr;

    // check if there is a piece at the square where the move ends and store it
    if (to->getPiece() != nullptr) {
        capturedPiece = to->getPiece();
    }

    Move currMove = move;

    // determine move type, default is normal
    MoveType moveType = MoveType::Normal;
    if (piece->getPieceType() == PieceType::pawn) {
        if (to->getX() != from->getX() && capturedPiece == nullptr) {
            moveType = MoveType::EnPassant;
        } else if (to->getY() == 0 || to->getY() == 7) {
            moveType = MoveType::Promotion;
        } else if (from->getY() == 1 && to->getY() == 3) {
            moveType = MoveType::DoublePawn;
        } else if (capturedPiece != nullptr) {
            moveType = MoveType::Capture;
        }
    } else if (piece->getPieceType() == PieceType::king && abs(from->getX() - to->getX()) == 2) {
        moveType = MoveType::Castling;
    } else if (capturedPiece != nullptr) {
        moveType = MoveType::Capture;
    }

    currMove.setMoveType(moveType);

    // perform the move based on the move type
    if (currMove.getMoveType() == MoveType::Normal) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
    } else if (currMove.getMoveType() == MoveType::Capture) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
        currMove.setCapturedPiece(capturedPiece);
    } else if (currMove.getMoveType() == MoveType::EnPassant) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        Square* target = getSquare(to->getX(), from->getY());
        currMove.setCapturedPiece(target->getPiece());
        piece->setSquare(to);
        target->setPiece(nullptr);
    } else if (currMove.getMoveType() == MoveType::DoublePawn) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
    } else if (currMove.getMoveType() == MoveType::Castling) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
 
        // Kingside castling
        if (to->getX() == from->getX() + 2) {
            Square* rookFrom = getSquare(7, from->getY());
            Square* rookTo = getSquare(5, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookTo->setPiece(rook);
            rookFrom->setPiece(nullptr);
        }
        // Queenside castling
        else if (to->getX() == from->getX() - 2) {
            Square* rookFrom = getSquare(0, from->getY());
            Square* rookTo = getSquare(3, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookTo->setPiece(rook);
            rookFrom->setPiece(nullptr);
        }
    } else if (currMove.getMoveType() == MoveType::Promotion) {
        // check for capture first
        if (capturedPiece != nullptr) {
            currMove.setCapturedPiece(capturedPiece);
        }

        Piece *newPiece = nullptr;
        // determine the piece to promote to
        char promotedTo = currMove.getPromotedTo();
        switch (promotedTo) {
            case 'q':
                newPiece = new Queen(piece->getColour());
                break;
            case 'r':
                newPiece = new Rook(piece->getColour());
                break;
            case 'b':
                newPiece = new Bishop(piece->getColour());
                break;
            case 'n':
                newPiece = new Knight(piece->getColour());
                break;
            default:
                break;
        }
        // set the promoted pawn
        currMove.setPromotedPawn(piece);

        to->setPiece(newPiece);
        from->setPiece(nullptr);
        newPiece->setSquare(to);
        newPiece->setBoard(this);
    }

    // set piece's moved state
    piece->setHasMoved(true);
    piece->setBoard(this);

    // add move to stack
    moveStack.push_back(currMove);

    return true;
}


bool Board::movePiece(const Move& move) {
    // check if the move is legal
    if (!isMoveLegal(move)) {
        if (!controller->getCurrentPlayer()->isRobot()) {
            std::cout << "Illegal move, try again!" << std::endl;
        }
        return false;
    }

    Square* from = move.getFrom();
    Square* to = move.getTo();
    Piece* piece = from->getPiece();
    piece->setBoard(this);

    // check if there is a piece at the square where the move ends and store it
    Piece *capturedPiece = nullptr;
    if (to->getPiece() != nullptr) {
        capturedPiece = to->getPiece();
    }

    Move currMove = move;
    // determine move type, default is normal
    MoveType moveType = MoveType::Normal;

    if (piece->getPieceType() == PieceType::pawn) {
        if (to->getX() != from->getX() && capturedPiece == nullptr) {
            moveType = MoveType::EnPassant;
        } else if (to->getY() == 0 || to->getY() == 7) {
            moveType = MoveType::Promotion;
        } else if (from->getY() == 1 && to->getY() == 3) {
            moveType = MoveType::DoublePawn;
        } else if (capturedPiece != nullptr) {
            moveType = MoveType::Capture;
        }
    } else if (piece->getPieceType() == PieceType::king && abs(from->getX() - to->getX()) == 2) {
        moveType = MoveType::Castling;
    } else if (capturedPiece != nullptr) {
        moveType = MoveType::Capture;
    }

    currMove.setMoveType(moveType);

    // perform the move based on the move type
    if (currMove.getMoveType() == MoveType::Normal) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
    } else if (currMove.getMoveType() == MoveType::Capture) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
        currMove.setCapturedPiece(capturedPiece);
    } else if (currMove.getMoveType() == MoveType::EnPassant) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        Square* target = getSquare(to->getX(), from->getY());
        currMove.setCapturedPiece(target->getPiece());
        piece->setSquare(to);
        target->setPiece(nullptr);
    } else if (currMove.getMoveType() == MoveType::DoublePawn) {
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);
    } else if (currMove.getMoveType() == MoveType::Castling) {

        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);

        // Kingside castling
        if (to->getX() == from->getX() + 2) {
            Square* rookFrom = getSquare(7, from->getY());
            Square* rookTo = getSquare(5, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookTo->setPiece(rook);
            rookFrom->setPiece(nullptr);
            rook->setHasMoved(true);
        }
        // Queenside castling
        else if (to->getX() == from->getX() - 2) {
            Square* rookFrom = getSquare(0, from->getY());
            Square* rookTo = getSquare(3, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookTo->setPiece(rook);
            rookFrom->setPiece(nullptr);
            rook->setHasMoved(true);
        }
    } else if (currMove.getMoveType() == MoveType::Promotion) {
        // check for capture first
        if (capturedPiece != nullptr) {
            currMove.setCapturedPiece(capturedPiece);
        }

        Piece *newPiece = nullptr;
        char promotedTo = currMove.getPromotedTo();
        // determine the piece to promote to
        if (promotedTo == 'q' || promotedTo == 'Q') {
            newPiece = new Queen(piece->getColour());
        } else if (promotedTo == 'r' || promotedTo == 'R') {
            newPiece = new Rook(piece->getColour());
        } else if (promotedTo == 'b' || promotedTo == 'B') {
            newPiece = new Bishop(piece->getColour());
        } else if (promotedTo == 'n' || promotedTo == 'N') {
            newPiece = new Knight(piece->getColour());
        }
        // set the promoted pawn
        currMove.setPromotedPawn(piece);

        to->setPiece(newPiece);
        from->setPiece(nullptr);
        newPiece->setSquare(to);
        newPiece->setBoard(this);
    }

    // set piece's moved state
    piece->setHasMoved(true);
    piece->setBoard(this);

    // add move to stack
    moveStack.push_back(currMove);
    //update display
    notifyObservers();

    return true;
}

void Board::undoMove() {
    // check if there are any moves to undo
    if (moveStack.size() == 0) {
        return;
    }

    Move lastMove = moveStack.back();
    moveStack.pop_back();

    Square* from = lastMove.getFrom();
    Square* to = lastMove.getTo();
    Piece* piece = to->getPiece();
    piece->setBoard(this);

    // undo the move based on the move type
    //reverse move performance logic
    if (lastMove.getMoveType() == MoveType::Normal) {
        from->setPiece(piece);
        to->setPiece(nullptr);
        piece->setSquare(from);
    } else if (lastMove.getMoveType() == MoveType::Capture) {
        from->setPiece(piece);
        to->setPiece(lastMove.getCapturedPiece());
        piece->setSquare(from);

    } else if (lastMove.getMoveType() == MoveType::EnPassant) {
        from->setPiece(piece);
        to->setPiece(nullptr);
        Square* target = getSquare(to->getX(), from->getY());
        target->setPiece(lastMove.getCapturedPiece());
        piece->setSquare(from);
    } else if (lastMove.getMoveType() == MoveType::DoublePawn) {
        from->setPiece(piece);
        to->setPiece(nullptr);
        piece->setSquare(from);
    } else if (lastMove.getMoveType() == MoveType::Castling) {

        from->setPiece(piece);
        to->setPiece(nullptr);
        piece->setSquare(from);

        // Kingside castling
        if (to->getX() == from->getX() + 2) {
            Square* rookFrom = getSquare(5, from->getY());
            Square* rookTo = getSquare(7, from->getY());
            Piece* rook = rookFrom->getPiece();

            rookTo->setPiece(rook);
            rookFrom->setPiece(nullptr);
            rook->setHasMoved(false);
        }
        else if (to->getX() == from->getX() - 2) {
            Square* rookFrom = getSquare(3, from->getY());
            Square* rookTo = getSquare(0, from->getY());
            Piece* rook = rookFrom->getPiece();

            rookTo->setPiece(rook);
            rookFrom->setPiece(nullptr);
            rook->setHasMoved(false);
        }

    } else if (lastMove.getMoveType() == MoveType::Promotion) {
        delete piece;

        // static cast into pawn
        piece = static_cast<Pawn*>(lastMove.getPromotedPawn());
        from->setPiece(piece);
        to->setPiece(nullptr);

        piece->setSquare(from);
        piece->setBoard(this);

        // if a piece had been captured, undo it
        if (lastMove.getCapturedPiece() != nullptr) {
            Square* capturedSquare = lastMove.getTo();
            capturedSquare->setPiece(lastMove.getCapturedPiece());
        }
    }

    piece->setBoard(this);

    // find last move of piece in moveStack
    bool found = false;
    bool hasMoved = false;

    //compute hasMoved
    for (int i = moveStack.size() - 1; i >= 0; i--) {
        if (moveStack[i].getFrom()->getPiece() == piece) {
            hasMoved = true;
            break;
        }
        if (moveStack[i].getTo()->getPiece() == piece) {
            break;
        }
    }

    piece->setHasMoved(hasMoved);
}

bool Board::isInCheck(Colour colour) const {
    // find the king of the given colour
    Square* kingSquare = findKing(colour);
    if (kingSquare == nullptr) {
        return false;
    }

    // find all valid moves of all pieces of the opposite colour
    std::vector<Move> allValidMoves;

    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() != colour) {

                std::vector<Move> validMoves = piece->getValidMoves();

                allValidMoves.insert(allValidMoves.end(), validMoves.begin(), validMoves.end());
            }
        }
    }

    // check if any of the valid moves of the opposite colour are to the king's square
    for (const auto& move : allValidMoves) {
        if (move.getTo() == kingSquare) {
            return true;
        }
    }

    return false;
}


bool Board::isCheckmate(Colour colour) {
    // check if the given colour is in check
    if (!isInCheck(colour)) {
        return false;
    }

    // find all valid moves of all pieces of the given colour
    std::vector<Move> validMoves;
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece && piece->getColour() == colour) {
                std::vector<Move> temp = piece->getValidMoves();
                validMoves.insert(validMoves.end(), temp.begin(), temp.end());
            }
        }
    }

    // check if any valid moves of the given colour put the king out of check
    for (const auto& move : validMoves) {
        bool valid = overrideMovePiece(move);
        bool isCheck = isInCheck(colour);
        undoMove();
        
        if (!isCheck) {
            return false;
        }
    }

    return true;
}


bool Board::isStalemate(Colour colour) const {
    bool turn = (colour == Colour::White) ? true : false;
	std::vector<Move> moveList;

    // find all valid moves of all pieces of the given colour
	if (turn) {
        for (const auto& row : board) {
            for (const auto& square : row) {
                Piece* piece = square->getPiece();
                if (piece && piece->getColour() == Colour::Black) {
                    std::vector<Move> temp = piece->getValidMoves();
                    moveList.insert(moveList.end(), temp.begin(), temp.end());
                }
            }
        }

	} else {
        for (const auto& row : board) {
            for (const auto& square : row) {
                Piece* piece = square->getPiece();
                if (piece && piece->getColour() == Colour::White) {
                    std::vector<Move> temp = piece->getValidMoves();
                    moveList.insert(moveList.end(), temp.begin(), temp.end());
                }
            }
        }
	}

    //if no moves are available, it is a stalemate
    if (moveList.size() == 0) {
        return true;
    }

	//loop through the board and check that it isn't only 2 kings left
    int pieceCount = 0;
    for (const auto& row : board) {
        for (const auto& square : row) {
            if (square->getPiece() != nullptr) {
                pieceCount++;
            }
        }
    }

    if (pieceCount == 2) {
        return true;
    }

    return false;
}

MoveType Board::determineMoveType(const Move& move) {
    //based off move attributes, determine the type of move
    //helper function for robots
    Square* from = move.getFrom();
    Square* to = move.getTo();
    Piece* piece = from->getPiece();
    Piece* capturedPiece = to->getPiece();

    if (piece->getPieceType() == PieceType::pawn) {
        if (to->getX() != from->getX() && capturedPiece == nullptr) {
            return MoveType::EnPassant;
        } else if (to->getY() == 0 || to->getY() == 7) {
            return MoveType::Promotion;
        } else if (from->getY() == 1 && to->getY() == 3) {
            return MoveType::DoublePawn;
        } else if (capturedPiece != nullptr) {
            return MoveType::Capture;
        }
    } else if (piece->getPieceType() == PieceType::king && abs(from->getX() - to->getX()) == 2) {
        return MoveType::Castling;
    } else if (capturedPiece != nullptr) {
        return MoveType::Capture;
    }

    return MoveType::Normal;
}