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
        }
    }
}

void Board::print() const {
    for (int i = 7; i >= 0; i--) {
        std::cout << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getPiece() == nullptr) {
                std::cout << "_";
            } else {
                std::cout << board[i][j]->getPiece()->getSymbol();
            }
        }
        std::cout << std::endl;
    }
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
            row.push_back(new Square(j, i));
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

    // for each of the pieces, set board and square
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();
            if (piece != nullptr) {
                piece->setBoard(this);
                piece->setSquare(square);
            }
        }
    }
}

void Board::addPiece(Piece* piece, Square* square) {
    square->setPiece(piece);
}

void Board::removePiece(Square* square) {
    if (square->getPiece() != nullptr) {
        delete square->getPiece();
    }
    square->setPiece(nullptr);
}

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
    // std::cout << "findKing called" << std::endl;
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();

            if (piece == nullptr) {
                // std::cout << "Piece at square" << square->getX() << " " << square->getY() << " is nullptr" << std::endl;
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

bool Board::isMoveLegal(const Move& move) const {
    Piece *piece = move.getFrom()->getPiece();

    if (piece == nullptr) {
        return false;
    }

    // print();

    // if (piece == nullptr) {
    //     std::cout << "piece is nullptr" << std::endl;
    // }

    std::vector<Move> validMoves = move.getFrom()->getPiece()->getValidMoves();
    // std::cout << "validMoves.size(): " << validMoves.size() << std::endl;

    // check if move is in validMoves
    return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
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

    // ensure neither king is in check
    if (isInCheck(Colour::White) || isInCheck(Colour::Black)) {
        return false;
    }

    return true;
}


bool Board::movePiece(const Move& move) {
    if (!isMoveLegal(move)) {
        std::cout << "Illegal move, try again!" << std::endl;
        return false;
    }

    Square* from = move.getFrom();
    Square* to = move.getTo();
    Piece* piece = from->getPiece();

    Move ourMove = move;

    // Handle castling
    if (piece->getPieceType() == PieceType::king && !(piece->getHasMoved())) {
        if (to->getX() == from->getX() + 2) {
            // Kingside castling
            Square* rookFrom = getSquare(7, from->getY());
            Square* rookTo = getSquare(5, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookFrom->setPiece(nullptr);
            rookTo->setPiece(rook);
            rook->setHasMoved(true);

            ourMove.setMoveType(MoveType::Castling);

        } else if (to->getX() == from->getX() - 2) {
            // Queenside castling
            Square* rookFrom = getSquare(0, from->getY());
            Square* rookTo = getSquare(3, from->getY());
            Piece* rook = rookFrom->getPiece();
            rookFrom->setPiece(nullptr);
            rookTo->setPiece(rook);
            rook->setHasMoved(true);

            ourMove.setMoveType(MoveType::Castling);
        }
    }

    // Handle en passant
    if (piece->getPieceType() == PieceType::pawn &&
        from->getX() != to->getX() && to->getPiece() == nullptr) {
        Square* target = getSquare(to->getX(), from->getY());
        target->setPiece(nullptr);
        ourMove.setMoveType(MoveType::EnPassant);
    }

    // Set piece as moved
    if (piece->getPieceType() == PieceType::king ||
        piece->getPieceType() == PieceType::rook) {
        piece->setHasMoved(true);
    }

    if (piece->getPieceType() == PieceType::pawn &&
        abs(to->getY() - from->getY()) == 2) {
        // static_cast<Pawn*>(piece)->setDashed(true);
        piece->setHasMoved(true);
        ourMove.setMoveType(MoveType::DoublePawn);
    }

    to->setPiece(piece);
    from->setPiece(nullptr);

    // Handle promotion
    if (piece->getPieceType() == PieceType::pawn && (to->getY() == 0 || to->getY() == 7)) {
        PieceType promotionType = controller->getPromotedTo();

        Piece* promotedPiece = nullptr;
        switch (promotionType) {
            case PieceType::queen:
                promotedPiece = new Queen(piece->getColour());
                break;
            case PieceType::rook:
                promotedPiece = new Rook(piece->getColour());
                break;
            case PieceType::bishop:
                promotedPiece = new Bishop(piece->getColour());
                break;
            case PieceType::knight:
                promotedPiece = new Knight(piece->getColour());
                break;
            default:
                break;
        }
        ourMove.setMoveType(MoveType::Promotion);
        to->setPiece(promotedPiece);
        delete piece;
    }

    // Handle capture
    if (to->getPiece() != nullptr) {
        ourMove.setMoveType(MoveType::Capture);
        ourMove.setCapturedPiece(to->getPiece());
        delete to->getPiece();
    }

    addMoveToStack(ourMove);
    notifyObservers();
    

    // Reset the moved state for pawns of the opposite color
    Colour oppositeColor = (piece->getColour() == Colour::White) ? Colour::Black : Colour::White;
    for (auto& row : board) {
        for (auto& square : row) {
            Piece* p = square->getPiece();
            if (p && p->getColour() == oppositeColor && p->getPieceType() == PieceType::pawn) {
                // static_cast<Pawn*>(p)->setDashed(false);
                p->setHasMoved(false);
            }
        }
    }
    return true;
}

void Board::undoMove() {
    if (moveStack.empty()) {
        return;
    }

    Move lastMove = moveStack.back();
    Square* from = lastMove.getFrom();
    Square* to = lastMove.getTo();

    Piece* piece = to->getPiece();
    from->setPiece(piece);

    // Handle capture
    if (lastMove.getCapturedPiece() != nullptr) {
        to->setPiece(lastMove.getCapturedPiece());
    } else {
        to->setPiece(nullptr);
    }

    // Handle castling
    if (piece->getPieceType() == PieceType::king && abs(from->getX() - to->getX()) == 2) {
        if (to->getX() == from->getX() + 2) {
            // Kingside castling
            Square* rookFrom = getSquare(5, from->getY());
            Square* rookTo = getSquare(7, from->getY());
            Piece* rook = rookTo->getPiece();
            rookTo->setPiece(nullptr);
            rookFrom->setPiece(rook);
        } else if (to->getX() == from->getX() - 2) {
            // Queenside castling
            Square* rookFrom = getSquare(3, from->getY());
            Square* rookTo = getSquare(0, from->getY());
            Piece* rook = rookTo->getPiece();
            rookTo->setPiece(nullptr);
            rookFrom->setPiece(rook);
        }
    }

    // Handle en passant
    if (piece->getPieceType() == PieceType::pawn &&
        from->getX() != to->getX() && to->getPiece() == nullptr) {
        Square* target = getSquare(to->getX(), from->getY());
        target->setPiece(new Pawn(piece->getColour()));
    }

    // Reset piece's moved state
    if (piece->getPieceType() == PieceType::king ||
        piece->getPieceType() == PieceType::rook) {
        piece->setHasMoved(false);
    }

    // Handle promotion
    if (piece->getPieceType() == PieceType::pawn && (to->getY() == 0 || to->getY() == 7)) {
        delete piece;
        to->setPiece(new Pawn(piece->getColour()));
    }

    moveStack.pop_back();
    notifyObservers();
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
    Square* kingSquare = findKing(colour);
    for (const auto& row : board) {
        for (const auto& square : row) {
            Piece* piece = square->getPiece();

            if (piece && piece->getColour() == colour) {

                // std::cout << "Piece at square (" << square->getX() << ", " << square->getY() << ") is " << piece->getSymbol() << std::endl;
                std::vector <Move> validMoves = piece->getValidMoves();

                // if (piece->getPieceType() == PieceType::pawn || piece->getPieceType() == PieceType::knight) {
                //     std::cout << "validMoves.size(): " << validMoves.size() << std::endl;
                // }
                // std::cout << "validMoves.size(): " << validMoves.size() << std::endl; // ZERO ??????
                for (const auto& move : validMoves) {
                    if (move.getTo() == kingSquare) {
                        return true;
                    }
                }
            }
        }
    }
    // std::cout << "return reached" << std::endl;
    return false;
}

bool Board::isCheckmate(Colour colour) const {

    if (!isInCheck(colour)) {
        return false;
    }

    // we know that the king is in check
    // we need to check if the king can move to a square that is not in check
    Square* kingSquare = findKing(colour);
    Piece* king = kingSquare->getPiece();
    std::vector<Move> validMoves = king->getValidMoves();

    for (const auto& move : validMoves) {
        if (move.getTo()->getPiece() == nullptr) {
            // move king to empty square
            Board tempBoard = *this;
            tempBoard.movePiece(move);
            if (!tempBoard.isInCheck(colour)) {
                return false;
            }
        } else {
            // capture the piece
            Board tempBoard = *this;
            tempBoard.movePiece(move);
            if (!tempBoard.isInCheck(colour)) {
                return false;
            }
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
