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
    string space = " ";
    out << " " << endl;
    out << "    abcdefgh" << endl;
    out << " " << endl;
    for (int i = 7; i >= 0; i--) {
        out << i+1 << "   ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->getPiece() == nullptr) {
                out << space;
            } else {
                out << board[i][j]->getPiece()->getSymbol();
            }
            space = (space == " ") ? "_" : " ";
        }
        out << "" << std::endl;
        space = (space == " ") ? "_" : " ";
    }
    out << " " << endl;
}