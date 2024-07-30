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

Board::Board() {
    setupInitialBoard();
}

Board::~Board() {
    for (auto& row : board) {
        for (auto& square : row) {
            delete square;
            square = nullptr;
            controller = nullptr;
        }
    }
}

void Board::print() const {
    for (int i = 7; i >= 0; i--) {
        std::cout << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getPiece() == nullptr && (i+j)%2 == 0) {
                std::cout << "_";
            } else if (board[i][j]->getPiece() == nullptr && (i+j)%2 == 1) {
                std::cout << " ";
            }
            else {
                std::cout << board[i][j]->getPiece()->getSymbol();
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  abcdefgh" << std::endl;
}

void Board::clearBoard() {
    for (auto& row : board) {
        for (auto& square : row) {
            if (square->getPiece() != nullptr) {
                delete square->getPiece();
            }
            square->setPiece(nullptr);
        }
    }
}

void Board::setupInitialBoard() {
    clearBoard();

    for (int i = 0; i < 8; i++) {
        std::vector<Square*> row;
        for (int j = 0; j < 8; j++) {
            Square* s = new Square(j, i);
            s->setBoard(this);
            row.push_back(s);
        }
        board.push_back(row);
    }

    // calls square's setPiece function
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
        whitePieces.push_back(board[1][i]->getPiece());
        whitePieces.push_back(board[0][i]->getPiece());
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
        blackPieces.push_back(board[6][i]->getPiece());
        blackPieces.push_back(board[7][i]->getPiece());
    }
}

std::vector<Piece*> Board::getWhitePieces() const {
    return whitePieces;
}

std::vector<Piece*> Board::getBlackPieces() const {
    return blackPieces;
}

void Board::addPiece(Piece* piece, Square* square) {
    square->setPiece(piece);
}

void Board::removePiece(Square* square) {
   if (square->getPiece() != nullptr) {
        delete square->getPiece();
    }
    square->setPiece(nullptr);}

std::vector<std::vector<Square*>> Board::getState() const {
    return board;
}

Square* Board::getSquare(int x, int y) const {
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return nullptr;
    }
    return board[y][x];
}

void Board::setController(Controller* ctrl) {
    controller = ctrl;
}

Square* Board::findKing(Colour colour) const {
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();

            if (piece == nullptr) {
            }

            if (piece && piece->getColour() == colour && piece->getPieceType() == PieceType::king) {
                return square;
            }
        }
    }
    // not found -- should never happen
    return nullptr;
}

void Board::addMoveToStack(const Move& move) {
    moveStack.push_back(move);
}

std::vector<Move> Board::getMoveStack() const {
    return moveStack;
}

Move Board::getLastMove() const {
    return moveStack.back();
}

bool Board::isMoveLegal(const Move& move) {
    if (move.getFrom()->getPiece() == nullptr) {
        return false;
    }
    Colour colour = move.getFrom()->getPiece()->getColour();

    // find all valid moves of all pieces of the given colour, that put the king out of check
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

    if (std::find(validMoves.begin(), validMoves.end(), move) == validMoves.end()) {
        return false;
    }

    bool isCheck1 = isInCheck(colour);
    bool valid = overrideMovePiece(move);
    bool isCheck2 = isInCheck(colour);
    undoMove();

    if (isCheck1 || isCheck2) {
        return false;
    }

    return true;
}




bool Board::isValidSetup() const {
    // check if there is exactly one king of each color
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

    // check if the kings are not next to each other from setup mode
    Square* whiteKing = findKing(Colour::White);
    Square* blackKing = findKing(Colour::Black);

    if (whiteKing->getX() == blackKing->getX() && abs(whiteKing->getY() - blackKing->getY()) == 1) {
        return false;
    }

    // ensure neither king is in check
    if (isInCheck(Colour::White) || isInCheck(Colour::Black)) {
        return false;
    }

    return true;
}

bool Board::overrideMovePiece(const Move& move) {
    Square* from = move.getFrom();
    Square* to = move.getTo();
    Piece* piece = from->getPiece();
    piece->setBoard(this);

    Piece *capturedPiece = nullptr;

    if (to->getPiece() != nullptr) {
        capturedPiece = to->getPiece();
    }

    Move currMove = move;

    // determine move type
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
        // PieceType promotedType = controller->getPromotedTo();
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

    Piece *capturedPiece = nullptr;
    if (to->getPiece() != nullptr) {
        capturedPiece = to->getPiece();
    }

    Move currMove = move;
    // determine move type
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

        // set king
        to->setPiece(piece);
        from->setPiece(nullptr);
        piece->setSquare(to);

        // set rook
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

        if (promotedTo == 'q' || promotedTo == 'Q') {
            newPiece = new Queen(piece->getColour());
        } else if (promotedTo == 'r' || promotedTo == 'R') {
            newPiece = new Rook(piece->getColour());
        } else if (promotedTo == 'b' || promotedTo == 'B') {
            newPiece = new Bishop(piece->getColour());
        } else if (promotedTo == 'n' || promotedTo == 'N') {
            newPiece = new Knight(piece->getColour());
        }

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

    notifyObservers();

    return true;
}

void Board::undoMove() {
    if (moveStack.size() == 0) {
        return;
    }

    Move lastMove = moveStack.back();
    moveStack.pop_back();

    Square* from = lastMove.getFrom();
    Square* to = lastMove.getTo();
    Piece* piece = to->getPiece();
    piece->setBoard(this);

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

// copy constructor
Board::Board(const Board& other) {
    for (const auto& row : other.board) {
        std::vector<Square*> newRow;
        for (const auto& square : row) {
            Square* newSquare = new Square(square->getX(), square->getY());
            if (square->getPiece() != nullptr) {
                Piece* piece = square->getPiece();
                Piece* newPiece = nullptr;
                switch (piece->getPieceType()) {
                    case PieceType::pawn:
                        newPiece = new Pawn(piece->getColour());
                        break;
                    case PieceType::rook:
                        newPiece = new Rook(piece->getColour());
                        break;
                    case PieceType::knight:
                        newPiece = new Knight(piece->getColour());
                        break;
                    case PieceType::bishop:
                        newPiece = new Bishop(piece->getColour());
                        break;
                    case PieceType::queen:
                        newPiece = new Queen(piece->getColour());
                        break;
                    case PieceType::king:
                        newPiece = new King(piece->getColour());
                        break;
                    default:
                        break;
                }
                newPiece->setHasMoved(piece->getHasMoved());
                newSquare->setPiece(newPiece);
                newPiece->setBoard(this);
            }
            newRow.push_back(newSquare);
        }
        board.push_back(newRow);
    }
}

// assignment operator
Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }

    for (auto& row : board) {
        for (auto& square : row) {
            delete square;
        }
    }
    board.clear();

    for (const auto& row : other.board) {
        std::vector<Square*> newRow;
        for (const auto& square : row) {
            Square* newSquare = new Square(square->getX(), square->getY());
            if (square->getPiece() != nullptr) {
                Piece* piece = square->getPiece();
                Piece* newPiece = nullptr;
                switch (piece->getPieceType()) {
                    case PieceType::pawn:
                        newPiece = new Pawn(piece->getColour());
                        break;
                    case PieceType::rook:
                        newPiece = new Rook(piece->getColour());
                        break;
                    case PieceType::knight:
                        newPiece = new Knight(piece->getColour());
                        break;
                    case PieceType::bishop:
                        newPiece = new Bishop(piece->getColour());
                        break;
                    case PieceType::queen:
                        newPiece = new Queen(piece->getColour());
                        break;
                    case PieceType::king:
                        newPiece = new King(piece->getColour());
                        break;
                    default:
                        break;
                }
                newPiece->setHasMoved(piece->getHasMoved());
                newSquare->setPiece(newPiece);
            }
            newRow.push_back(newSquare);
        }
        board.push_back(newRow);
    }

    return *this;
}

bool Board::isInCheck(Colour colour) const {
    // check if the king of the given colour is in check
    Square* kingSquare = findKing(colour);
    if (kingSquare == nullptr) {
        std::cout << "King not found!!!" << std::endl;
        return false;
    }

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

    for (const auto& move : allValidMoves) {
        if (move.getTo() == kingSquare) {
            return true;
        }
    }

    return false;
}


bool Board::isCheckmate(Colour colour) {

    if (!isInCheck(colour)) {
        return false;
    }

    // find all valid moves of all pieces of the given colour, that put the king out of check
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

    for (const auto& move : validMoves) {
        bool valid = overrideMovePiece(move);
        Colour checkColour = (colour == Colour::White) ? Colour::Black : Colour::White;
        bool isCheck = isInCheck(checkColour);
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

    if (moveList.size() == 0) {
        return true;
    }

	return false;
}

std::vector<std::vector<Square*>> Board::getBoard() {
    return board;
}
