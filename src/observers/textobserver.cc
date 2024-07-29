#include "textobserver.h"
#include "board.h"

TextObserver::TextObserver(Subject &sub, std::ostream &out) : subject(sub), out(out) {
    subject.attach(this);
}

TextObserver::~TextObserver() {
    subject.detach(this);
}

void TextObserver::notify() {
    std::vector<std::vector<Square*>> board = subject.getState();
    for (int i = 7; i >= 0; i--) {
        out << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getPiece() == nullptr && (i+j)%2 == 0) {
                out << "_";
            } 
            else if (board[i][j]->getPiece() == nullptr && (i+j)%2 == 1) {
                out << " ";
            }
            else {
                out << board[i][j]->getPiece()->getSymbol();
            }
        }
        out << std::endl;
    }
    out << "  abcdefgh" << std::endl;
}
